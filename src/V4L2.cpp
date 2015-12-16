/////////////////////////////////////////////////////////////////////////////////////////
//V4L2.cpp
//符合V4L2协议的摄像机的接口函数
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
#include "V4L2.h"
#include <stdio.h>

#define MAX_FAILURE_COUNT					20

/////////////////////////////////////////////////////////////////////////////////////////
//打开摄像头设备文件
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int open_device(V4L2_data *camera)
{
	if (-1 == (camera->fd = open (camera->dev_name, O_RDWR | O_NONBLOCK, 0)))
		return -1;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//初始化摄像头设备
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_device(V4L2_data* camera)
{
	//查询设备驱动的功能
	v4l2_capability cap;
	if (-1 == ioctl (camera->fd, VIDIOC_QUERYCAP, &cap))
		return -11;
	//若不支持视频捕获功能则退出
	if (! (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
		return -12;
	if (! (cap.capabilities & V4L2_CAP_STREAMING))
		return -13;
		
	//设置视频设备的视频数据格式
	v4l2_format fmt;
	memset(&fmt, 0, sizeof(v4l2_format));
	fmt.type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width	= IMAGE_WIDTH;
	fmt.fmt.pix.height	= IMAGE_HEIGHT;
	fmt.fmt.pix.pixelformat	= V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field	= V4L2_FIELD_INTERLACED;
	if (-1 == ioctl (camera->fd, VIDIOC_S_FMT, &fmt))
		return -14;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//分配视频缓冲区
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_mmap(V4L2_data *camera)
{
	//请求V4L2驱动分配视频缓冲区（申请V4L2视频驱动分配内存）
	v4l2_requestbuffers req;
	memset(&req, 0, sizeof(v4l2_requestbuffers));
	req.count	=	2;									//申请的缓冲区的个数
	req.type	=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory	=	V4L2_MEMORY_MMAP;					//mmap方式
	if(-1 == ioctl (camera->fd, VIDIOC_REQBUFS, &req))
		return -21;
	//若只申请到1个或没有申请到缓冲区，则返回
	if(req.count < 2)
		return -22;

	//将内核空间地址映射到用户空间，方便应用程序的访问
	v4l2_buffer v4l2_buf;
	camera->n_buffers = req.count;
	camera->buffers = (image_buffer *)calloc (camera->n_buffers, sizeof (image_buffer));
	for (int i = 0; i < camera->n_buffers; ++i )
	{
		memset(&v4l2_buf, 0, sizeof(v4l2_buffer));
		v4l2_buf.type	=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
		v4l2_buf.memory	=	V4L2_MEMORY_MMAP;
		v4l2_buf.index	=	i;
		if (-1 == ioctl (camera->fd, VIDIOC_QUERYBUF, &v4l2_buf))
			return -23;

		camera->buffers[i].length	=	v4l2_buf.length;
		camera->buffers[i].start	= mmap(NULL,		/*start anywhere*/
				v4l2_buf.length,
				PROT_READ | PROT_WRITE,
				MAP_SHARED,
				camera->fd,
				v4l2_buf.m.offset);
		if (MAP_FAILED == camera->buffers[i].start)
			return -24;	
			
		//投放空的视频缓冲区到视频缓冲区输入队列中
		if (-1 == ioctl (camera->fd, VIDIOC_QBUF, &v4l2_buf))
			return -25;
	}
	
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//启动视频采集
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int start_capturing(V4L2_data *camera)
{
	//启动视频采集
	enum v4l2_buf_type type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl (camera->fd, VIDIOC_STREAMON, &type))
		return -31;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//打开并初始化摄像头设备，启动视频采集
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_dev (V4L2_data *camera)
{
	camera->failure_count = 0;
	camera->frame_index = 0;
	
	//打开摄像头设备
	int error_code = open_device(camera);
	if(error_code < 0 )
		return error_code;
	
	//设置分辨率等参数
	error_code = init_device(camera);
	if(error_code < 0 )
		return error_code;

	//分配缓存
	error_code = init_mmap(camera);
	if(error_code < 0 )
		return error_code;

	//启动视频采集
	error_code = start_capturing(camera);
	if(error_code < 0 )
		return error_code;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//停止摄像头设备
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void stop_dev (V4L2_data *camera)
{
	//停止视频采集
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl (camera->fd, VIDIOC_STREAMOFF, &type);

	//释放分配的空间
	for (int i = 0; i < camera->n_buffers; ++i)
		munmap(camera->buffers[i].start, camera->buffers[i].length);
	
	//关闭摄像头
	close(camera->fd);
}


/////////////////////////////////////////////////////////////////////////////////////////
//YUV转RGB函数
//参数：img_8u2_yuyv——输入图像YUYV
//      img_8u3_rgb——输出图像RGB
//      img_width——图像宽度
//      img_height——图像高度
//////////////////////////////////////////////////////////////////////////
void Yuv2Rgb(unsigned char *img_8u2_yuyv,
			unsigned char *img_8u3_rgb, 
			const int img_width, 
			const int img_height)
{
	int i;
	
	//YUV图像的尺寸
	int yuv_size = img_width * img_height * 2;
	
	//像素在图像数据中的偏移量
	int offset_rgb = 0;
	int offset_yuv = 0;
	
	//YUYV值
	int y0, u, y1, v;
	//RGB补偿值
	int delta_r, delta_g, delta_b;

	//截断查找表及其赋值，限定输出值范围为[0,255]，具体调用方式为f(x)=table_cut[x+512]
	unsigned char table_cut[1024];
	for(i=0; i<512; i++)
		table_cut[i] = 0;
	for(i=512; i<768; i++)
		table_cut[i] = i-512;
	for(i=768; i<1024; i++)
		table_cut[i] = 255;

	//将图像中的每一个YUYV值转化为2对RGB值
	for(offset_yuv = 0; offset_yuv < yuv_size; offset_yuv += 4) 
	{
		//得到YUYV值
		y0 = img_8u2_yuyv[offset_yuv] + 512;			//512为查表的0位置
  		u  = img_8u2_yuyv[offset_yuv + 1] - 128;		//128为色度的0位置
  		y1 = img_8u2_yuyv[offset_yuv + 2] + 512;		//512为查表的0位置
  		v  = img_8u2_yuyv[offset_yuv + 3] - 128;		//128为饱和度的0位置
		
		//得到UV的修正值
		delta_r = (351*v)>>8;                         	
		delta_g = -( (179*v + 86*u)>>8 );	
		delta_b = (444*u)>>8;

		//得到转化后的RGB值
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_r];
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_g];
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_b];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_r];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_g];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_b];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//YUV转Gray函数
//参数：img_8u2_yuyv——输入图像YUYV
//      img_8u1_gray——输出图像Gray
//      img_width——图像宽度
//      img_height——图像高度
/////////////////////////////////////////////////////////////////////////////////////////
void Yuv2Gray(const unsigned char *img_8u2_yuyv,
			unsigned char *img_8u1_gray,
			const int img_width, 
			const int img_height)
{
	int gray_size = img_width * img_height;
	int offset;
	for(offset = 0; offset < gray_size; offset ++) 
		img_8u1_gray[offset] = img_8u2_yuyv[offset<<1];
}

/////////////////////////////////////////////////////////////////////////////////////////
//重新启动摄像头设备
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void restart_dev (V4L2_data *camera)
{
	//停止视频采集
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl (camera->fd, VIDIOC_STREAMOFF, &type);

	//释放分配的空间
	for (int i = 0; i < camera->n_buffers; ++i)
		munmap(camera->buffers[i].start, camera->buffers[i].length);
	
	//关闭摄像头
	close(camera->fd);
	
	//启动摄像头
	if(open_device(camera) < 0 )
		return;
	if(init_device(camera) < 0 )
		return;
	if(init_mmap(camera) < 0 )
		return;
	start_capturing(camera);
	
	camera->failure_count = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//读取帧图像
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int read_frame(V4L2_data *camera, 
				unsigned char *img_8u3_rgb888, 				/*输出的RGB888数据*/
				unsigned char *img_8u1_gray)				/*输出的灰度图像数据*/
{
	//当前拍摄的视频数据的缓冲区
	v4l2_buffer			current_buf;			
	memset(&current_buf, 0, sizeof(v4l2_buffer));
	current_buf.type	=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
	current_buf.memory	= 	V4L2_MEMORY_MMAP;
	ioctl (camera->fd, VIDIOC_DQBUF, &current_buf);
	
	//缓冲区地址
	unsigned char *img_buffer = (unsigned char *)(camera->buffers[current_buf.index].start);
	
	if(current_buf.bytesused != IMAGE_WIDTH*IMAGE_HEIGHT*2)
	{	
		//释放当前读取图像的缓存
		printf("yuyv size Error! \n");
		camera->failure_count++;
		ioctl(camera->fd, VIDIOC_QBUF, &current_buf);
			
		//若多次出现yuyv size Error，说明摄像头出现了故障，重启摄像头
		if(camera->failure_count > MAX_FAILURE_COUNT)
		{
			printf("yuyv capturing error, restart! \n");
			restart_dev(camera);
		}
		return 0;
	}
	camera->failure_count = 0;
	
	//图像格式转换，YUV----RGB
	if(NULL != img_8u3_rgb888)
	{
		Yuv2Rgb(
			img_buffer, 
			img_8u3_rgb888, 
			IMAGE_WIDTH, 
			IMAGE_HEIGHT);
	}
	
	//图像格式转换，YUV----GRAY
	if(NULL != img_8u1_gray)
	{
		Yuv2Gray(
			img_buffer, 
			img_8u1_gray, 
			IMAGE_WIDTH, 
			IMAGE_HEIGHT);
	}
	
	//释放当前读取图像的缓存
	ioctl(camera->fd, VIDIOC_QBUF, &current_buf);
	
	camera->frame_index++;
	
	return 1;
}

