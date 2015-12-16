//
//  main.cpp
//  detectellipse
//
//  Created by 杨朔柳 on 15/12/13.
//  Copyright © 2015年 杨朔柳. All rights reserved.
//

#define __ARM__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>

#ifdef __ARM__
#include "V4L2.h"
#endif



const int TH_COLOR_TARGET_H=140;            //目标颜色阈值
const double TH_COLOR_TARGET_S=0.66;
const double TH_COLOR_TARGET_V=0.91;

const int TH_AREA_NOISE_LOW=50;                 //目标面积阈值
const int TH_AREA_NOISE_HIGH=1000;

const int TOL_COLOR_TARGET_H=10;                //目标颜色误差
const int TOL_COLOR_TARGET_S=0.03;
const int TOL_COLOR_TARGET_V=0.03;

using namespace std;
using namespace cv;
//
//HSV颜色空间阈值化
void ColorThreshold(IplImage * _src, IplImage * _binary, int th_h, int h0,double th_s,double s0,double th_v,int v0)
{
    char * data = _src->imageData;
    float * h, *s, *v;
    for (int i = 0; i < _src->height; i++)
    {
        for (int j = 0; j < _src->width; j++)
        {
            h = (float*)((data)+i*_src->widthStep + j*(_src->nChannels*sizeof(float)));
            s = (float*)((data)+i*_src->widthStep + j*(_src->nChannels*sizeof(float))+1);
            v = (float*)((data)+i*_src->widthStep + j*(_src->nChannels*sizeof(float))+2);
            int diff_h=*h-h0;
            double diff_s=*s-s0;
            double diff_v=*v-v0;
            if ((diff_h > 0 ? diff_h : -diff_h) < th_h &&
                (diff_s > 0 ? diff_s : -diff_s) < th_s &&
                (diff_v > 0 ? diff_v : -diff_v) < th_v)
            {
                *(_binary->imageData + i*_binary->widthStep + j*_binary->nChannels) = 255;
            }
            else
            {
                *(_binary->imageData + i*_binary->widthStep + j*_binary->nChannels) = 0;
            }
        }
    }
}
int main(int argc, const char * argv[])
{
#ifdef __PC__
    VideoCapture cam(0);
    Mat frame;
    IplImage trans;
#elif defined __ARM__
    V4L2_data v4l2Camara;
    memset(&v4l2Camara, 0, sizeof(V4L2_data));
    v4l2Camara.dev_name = (char *)("/dev/video0");
    int v4l2Code=init_dev(&v4l2Camara);
#endif
    
    //输入图像，灰度图像，二值图像，轮廓
    IplImage * input, *gray, *binary, *img_coutours;
    int read_code=0;

#ifdef __PC__
    //用C++接口输入，Mat转换为IplImage
    if(cam.isOpened() == false)
    {
        cerr<<"Can not open camara\n";
        return -1;
    }
    cam>>frame;
    if(frame.empty() == true)
    {
        cerr<<"Can not load video from camara\n";
        return -1;
    }
    read_code=1;
    trans=frame;
    input=&trans;
    cvNamedWindow("coutours");
    
    
#elif defined __ARM__
    if(v4l2Code < 0)
    {
        cerr<<"Can not open camara\n";
        return -1;
    }
    input=cvCreateImageHeader(cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),8,3);
    
    if((read_code=read_frame(&v4l2Camara, (unsigned char *)input->imageData,NULL) )!= 1)
    {
        cerr<<"Can not load video from camara\n";
        return -1;
    }
#endif
    gray = cvCreateImage(cvGetSize(input), input->depth, 1);
    binary = cvCreateImage(cvGetSize(input), input->depth, 1);
    img_coutours = cvCreateImage(cvGetSize(input), input->depth, 3);
    //转换hsv之前要用32位深度的图像
    IplImage * input32=cvCreateImage(cvGetSize(input), 32, 3);
    IplImage * hsv=cvCreateImage(cvGetSize(input), 32, 3);
    cvZero(img_coutours);
    //轮廓存储
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq * seq = NULL;
    vector<CvSeq *> target;
    
    while(read_code == 1)
    {
#ifdef __PC__
        trans=frame;
        input=&trans;
#endif
        //cvCvtColor(input, gray, CV_BGR2GRAY);
        //cvThreshold(gray, binary, 0, 255, CV_THRESH_BINARY);
        //转换为32bit图像
        cvConvertScale(input, input32,1.0,0);
        cvCvtColor(input32, hsv, CV_BGR2HSV);
        //颜色滤波
        ColorThreshold(hsv,
                       binary,
                       TOL_COLOR_TARGET_H,TH_COLOR_TARGET_H,
                       TOL_COLOR_TARGET_S,TH_COLOR_TARGET_S,
                       TOL_COLOR_TARGET_V,TH_COLOR_TARGET_V);
        
        //腐蚀膨胀去噪
        cvErode(binary, binary);
        cvErode(binary, binary);
        cvDilate(binary, binary);
        cvDilate(binary, binary);
        //膨胀腐蚀连通
        cvDilate(binary, binary);
        cvDilate(binary, binary);
        cvErode(binary, binary);
        cvErode(binary, binary);
        
        //cvCanny(gray, binary, 50, 150);
        //外部轮廓
        cvFindContours(binary, storage, &seq, sizeof(CvContour),
                       CV_RETR_EXTERNAL,		//以线性表形式存储
                       CV_CHAIN_APPROX_NONE);	//
        target.clear();
        //对每一个轮廓进行面积几何滤波
        for(CvSeq * current = seq;current != NULL;current = current->h_next)
        {
            CvRect rect = cvBoundingRect(current);
            int area=rect.height*rect.width;
            if(!(area<TH_AREA_NOISE_LOW ||area>TH_AREA_NOISE_HIGH ))
            {
                target.push_back(current);
            }
        }
#ifdef __PC__
        for(int i=0;i<target.size();i++)
        {
            cvDrawContours(img_coutours,target[i],CvScalar(255,255,255), CvScalar(255,255,255), 0,1,8);
        }
#endif
        //层序遍历画轮廓
        
//        queue<CvSeq *> que;
//        for (CvSeq * sibling = seq; sibling != NULL; sibling = sibling->h_next)
//        {
//            que.push(sibling);
//        }
//        while (que.empty() == false)
//        {
//            CvSeq * s = que.front();
//            //draw contours
//            cvDrawContours(img_coutours, s,
//                           CvScalar(255, 0, 0),
//                           CvScalar(0, 255, 0),
//                           0,					//max_level
//                           1,
//                           8);
//            //fit ellipse
//            if(s->total > 20)
//            {
//                
//            }
//            CvBox2D b = cvFitEllipse2(s);
//            b.angle = 90 - b.angle;
//            printf("-----------------\narea:%f\n", cvContourArea(s));
//            printf("arclenth:%f\n", cvArcLength(s));
//            printf("enter of ellipse:(%f %f)\n", b.center.x, b.center.y);
//            printf("width and height:%d %d\n------------------\n", b.size.width, b.size.height);
//            
//            que.pop();
//            for (CvSeq * child = s->v_next; child != NULL; child = child->h_next)
//            {
//                que.push(child);
//            }
//        }
#ifdef __PC__
	cvShowImage("coutours",binary);
        cam>>frame;
	if(frame.empty() == false)
	{
	    read_code = 1;
	}
	else
	{
	    read_code = 0;
	}
#elif defined (__ARM__)
        read_code=read_frame(&v4l2Camara, (unsigned char *)input->imageData,NULL);
#endif
        cvClearMemStorage(storage);
    }
    
#ifdef __PC__
    cvDestroyWindow("coutours");
#endif
    return 0;

}
