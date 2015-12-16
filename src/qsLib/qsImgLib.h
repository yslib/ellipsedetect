/////////////////////////////////////////////////////////////////////////////////////////
//qsImgLib.h
//ͼ�����ú����Ķ���ͷ�ļ�
//����Ƕ�ӿƼ����޹�˾      http://shop111408299.taobao.com/
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__QSIMGLIB_H__
#define		__QSIMGLIB_H__

#define 	QS_ZERO						0.0000001
#define 	QS_PI						3.1415926

#define		RETURN_SUCESS				1
#define		RETURN_FAILURE				0

#ifdef __cplusplus
extern "C" {
#endif



/////////////////////////////////////////////////////////////////////////////////////////
//JPEG���뺯��
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsJpegDecode(
		unsigned char **yuyv, 				//����Ľ�����YUYVͼ��
		unsigned char *jpeg_buf, 			//���������ɼ�����MJPEG������
		int *width, 						//����õ���ͼ����
		int *height);						//����õ���ͼ��߶�

/////////////////////////////////////////////////////////////////////////////////////////
//����MJPEG�����õ�JPEGͼ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsJpegSave(
		unsigned char *jpeg_buf,			//���������ɼ�����MJPEG������
		int jpeg_size,						//MJPEG�������Ĵ�С
		char file_name[1024]);				//�ļ���

		
		
		
/////////////////////////////////////////////////////////////////////////////////////////
//���ڴ�����д��ָ�����ļ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsDataSave(
		const void *data_ptr,				//����Ĵ�д������ݵ�ַ
		const int len,						//���ݳ���
		const char filename[1024]);			//Ҫд����ļ����ļ���

/////////////////////////////////////////////////////////////////////////////////////////
//��ָ�����ļ��е����ݶ�ȡ���ڴ���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsDataLoad(
		void *data_ptr,						//��ȡ�����ݴ�ŵ�ַ
		const int len,						//Ҫ��ȡ�����ݳ���
		const char filename[1024]);			//Ҫ��ȡ���ļ����ļ���
			  
/////////////////////////////////////////////////////////////////////////////////////////
//����RGB����ΪBMPͼ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBmpRgbSave(
		const unsigned char* img_8u3_src,	//�����RGBͼ������
		const int width,					//ͼ����
		const int height,					//ͼ��߶�
		const char filename[1024],			//�ļ���
		const int trans_flag);				//������ͼ��ΪQT�е�RGB888��ʽ(ԭ�����Ͻ�)������Ҫ���и�ʽת������ֵ1������ֵ0
		
/////////////////////////////////////////////////////////////////////////////////////////
//����RGB��ʽ��BMPͼ��������ģ��ƥ��Ļ�׼ͼ��Ӧ�ó���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsBmpRgbLoad(
		unsigned char* img_8u3_load,		//�����RGBͼ������
		int* width,							//��ȡ��ͼ����
		int* height,						//��ȡ��ͼ��߶�
		const char filename[1024],			//�ļ���
		const int trans_flag);				//����������ͼ���ʽΪQT�е�RGB888��ʽ(ԭ�����Ͻ�)������Ҫ���и�ʽת������ֵ1������ֵ0

/////////////////////////////////////////////////////////////////////////////////////////
//����GRAYͼ������ΪBMPͼ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBmpGraySave(
		const unsigned char* img_8u1_src,	//�����GRAYͼ������
		const int width,					//ͼ����
		const int height,					//ͼ��߶�
		const char filename[1024],			//�ļ���
		const int trans_flag);				//������ͼ��ΪQT�е�ͼ���ʽ(ԭ�����Ͻ�)������Ҫ���и�ʽת������ֵ1������ֵ0		

/////////////////////////////////////////////////////////////////////////////////////////
//����Ҷ�ͼ���ʽ��BMPͼ��������ģ��ƥ��Ļ�׼ͼ��Ӧ�ó���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsBmpGrayLoad(
		unsigned char* img_8u1_load,		//�����GRAYͼ������
		int* width,							//��ȡ��ͼ����
		int* height,						//��ȡ��ͼ��߶�
		const char filename[1024],			//�ļ���
		const int trans_flag);				//����������ͼ���ʽΪQT�е�ͼ���ʽ(ԭ�����Ͻ�)������Ҫ���и�ʽת������ֵ1������ֵ0
		
typedef struct
{
	int 	left;
	int 	right;
	int 	top;
	int 	bottom;
}QSRECT;

/////////////////////////////////////////////////////////////////////////////////////////
//����ο�Ŀ��ߡ����
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
int qsRectWidth(const QSRECT rc0);
int qsRectHeight(const QSRECT rc0);
int qsRectArea(const QSRECT rc0);

/////////////////////////////////////////////////////////////////////////////////////////
//�����ο�ĸ���Ԫ���޶���һ����ȡֵ��Χ��
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsRectSetRange(
		QSRECT *rc0, 						//��ʼ��Ϊ������ο�������ƺ�ľ��ο�
		const int min_w, 					//�޶����ο�(left,right)����Сֵ��ͨ���趨Ϊ0
		const int min_h,					//�޶����ο�(top,bottom)����Сֵ��ͨ���趨Ϊ0
		const int max_w, 					//�޶����ο�(left,right)�����ֵ��ͨ���趨ΪIMAGE_WIDTH-1
		const int max_h); 					//�޶����ο�(top,bottom)�����ֵ��ͨ���趨ΪIMAGE_HEIGHT-1
		
/////////////////////////////////////////////////////////////////////////////////////////
//���������ž��ο򣬷���ֵΪ���ź�ľ��ο�
//Ӧ���еõ����ź�ľ��ο����Ҫ����qsRectSetRange��Ԫ��ȡֵ��������
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
QSRECT qsRectScale(
		const QSRECT rc0, 					//������ο�
		const float ratio);					//���ο�����ű���

/////////////////////////////////////////////////////////////////////////////////////////
//���������ο�Ľ����Ĵ�С
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
int qsRectCrossArea(const QSRECT rc1, const QSRECT rc2);

/////////////////////////////////////////////////////////////////////////////////////////
//���������ο�Ĳ����Ĵ�С
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
int qsRectUionArea(const QSRECT rc1, const QSRECT rc2);

/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ�����ο�
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddRectToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSRECT rc0,					//Ҫ��ӵľ��ο��λ��
		const int line_thick,				//������ȣ���λΪ����
		const int r, 						//Ҫ��ӵľ��ο����ɫ-red
		const int g, 						//Ҫ��ӵľ��ο����ɫ-green
		const int b);						//Ҫ��ӵľ��ο����ɫ-blue
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ��+
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddCrossToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const int x0,	const int y0,		//Ҫ��ӵ�+��λ��
		const int half_cross_len,			//Ҫ��ӵ�+�ĳ��ȵ�һ�룬��λΪ����
		const int half_cross_thick,			//Ҫ��ӵ�+�Ŀ�ȵ�һ�룬��λΪ����
		const int r, 						//Ҫ��ӵ�+����ɫ-red
		const int g, 						//Ҫ��ӵ�+����ɫ-green
		const int b);						//Ҫ��ӵ�+����ɫ-blue
		
/////////////////////////////////////////////////////////////////////////////////////////
//�Ѷ�ֵͼ���ǰ�����֣�255��������ʾ��rgbͼ�����Թ���ʾ
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryOverlayImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const unsigned char *img_8u1_binary,//��ֵͼ��
		const int r, 						//���ӵ���ɫ-red
		const int g, 						//���ӵ���ɫ-green
		const int b,						//���ӵ���ɫ-blue
		const float alfa);					//��ɫ������ӻ�͸����, 0-1,1��ʾȫ����

/////////////////////////////////////////////////////////////////////////////////////////
//ֻ��ʾ��ֵͼ���ǰ�����֣�255����Ӧ�ĳ���ͼ��
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryOcupyImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const unsigned char *img_8u1_binary);//��ֵͼ��		
		
/////////////////////////////////////////////////////////////////////////////////////////
//�õ���ͼ������,gray
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsBlockImageDataGray(
		const unsigned char *img_8u1_src,	//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const int left,						//��ͼ��������ͼ���е���ʼλ�á���x����
		const int top,						//��ͼ��������ͼ���е���ʼλ�á���y����
		const int block_width,				//Ҫȡ�õĿ�ͼ��Ŀ��
		const int block_height,				//Ҫȡ�õĿ�ͼ��ĸ߶�
		unsigned char *img_8u1_block);		//���صĿ�ͼ������
		
/////////////////////////////////////////////////////////////////////////////////////////
//�õ���ͼ������,rgb
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsBlockImageDataRgb(
		const unsigned char *img_8u3_src,	//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const int left,						//��ͼ��������ͼ���е���ʼλ�á���x����
		const int top,						//��ͼ��������ͼ���е���ʼλ�á���y����
		const int block_width,				//Ҫȡ�õĿ�ͼ��Ŀ��
		const int block_height,				//Ҫȡ�õĿ�ͼ��ĸ߶�
		unsigned char *img_8u3_block);		//���صĿ�ͼ������
		
/////////////////////////////////////////////////////////////////////////////////////////
//��4���Ҷ�ͼ��ϲ�����2��2��ʾ�����ͼ��Ĵ�С������ͼ���Сһ��
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsMerge4Image(
		unsigned char *img_8u1_src1,		//����Ҷ�ͼ������1
		unsigned char *img_8u1_src2,		//����Ҷ�ͼ������2
		unsigned char *img_8u1_src3,		//����Ҷ�ͼ������3
		unsigned char *img_8u1_src4,		//����Ҷ�ͼ������4
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		unsigned char *img_8u1_dst);		//����ĺϲ���ĻҶ�ͼ������
		
					

		
		
	
//////////////////////////////////////////////////////////////////////////
//MFC��BGR888��ʽ��ԭ�����½ǣ���QT�е�RGB888��ʽ(ԭ�����Ͻ�)֮����໥ת��
//Author��EmbedVison
//////////////////////////////////////////////////////////////////////////
void qsRgbFormatWinQtTrans(
		const unsigned char *img_8u3_in,	//�����win��qtͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		unsigned char *img_8u3_out);		//�����qt��win��ͼ������

//////////////////////////////////////////////////////////////////////////
//MFC�лҶ�ͼ���ʽ��ԭ�����½ǣ���QT�еĻҶ�ͼ���ʽ(ԭ�����Ͻ�)֮����໥ת��
//Author��EmbedVison
//////////////////////////////////////////////////////////////////////////
void qsGrayFormatWinQtTrans(
		const unsigned char *img_8u1_in,	//�����win��qtͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		unsigned char *img_8u1_out);		//�����qt��win��ͼ������
		
/////////////////////////////////////////////////////////////////////////////////////////
//YUVתRGB����
//Author��EmbedVison
//////////////////////////////////////////////////////////////////////////
void qsYuv2Rgb(
		const unsigned char *img_8u2_yuyv,	//����ͼ��YUYV
		unsigned char *img_8u3_rgb, 		//���ͼ��RGB
		const int img_width, 				//ͼ����
		const int img_height);				//ͼ��߶�
		
/////////////////////////////////////////////////////////////////////////////////////////
//YUVתGray����
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsYuv2Gray(
		const unsigned char *img_8u2_yuyv,	//����ͼ��YUYV
		unsigned char *img_8u1_gray,		//���ͼ��Gray
		const int img_width, 				//ͼ����
		const int img_height);				//ͼ��߶�
		
/////////////////////////////////////////////////////////////////////////////////////////
//��RGBͼ��ת��Ϊ�Ҷ�ͼ��ĺ�������Ƕ��ʽӦ��������qsYuv2Gray��ûҶ�ͼ���Ч�ʸ���
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsRgb2Gray(
		const unsigned char *img_8u3_src,	//����ԴRGBͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		unsigned char *img_8u1_dst);		//����ı任���GRAYͼ������
		
/////////////////////////////////////////////////////////////////////////////////////////
//�ѻҶ�ͼ��ת��ΪRGBͼ��ĺ������Թ�ͼ����MFC����Qt�Ľ�������ʾ�������㷨��
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsGray2Rgb(
		const unsigned char *img_8u1_src,	//����ԴGRAYͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		unsigned char *img_8u3_dst);		//����ı任���RGBͼ������


	

	
	
/////////////////////////////////////////////////////////////////////////////////////////
//��ȡ��ת�����ź��ͼ��ĺ�����ֻ���������ͼ��ͬ����С�����ͼ��
//�����������ֲü��������㲿����0���䣬��ת�����趨Ϊͼ������
//�˺����������ɻ�׼����������ͬ�߶���Ƕ��µ�ѵ������
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsTransformImg(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		unsigned char *img_8u1_dst, 		//����ı任���ͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const float scale, 					//��Ҫ���ŵ�����
		const float sita);					//��Ҫ��ת�ĽǶ�
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ���ȡ��߶ȹ�һ������׼�ߴ�
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsNormalizeImg(
		const unsigned char *img_8u1_src,	//����Դͼ������
		const int img_width_src,			//����ͼ����
		const int img_height_src,			//����ͼ��߶�
		const int img_width_dst,			//ָ�������ͼ����	
		const int img_height_dst,			//ָ�������ͼ��߶�
		unsigned char *img_8u1_dst);		//���ͼ��
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ��ĻҶ�ֱ��ͼ
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsHistogram(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		int *hist);							//�����ֱ��ͼ
void qsHistogramRect(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const QSRECT rcROI,					//ָ����ͳ������
		int *hist);							//�����ֱ��ͼ
		
/////////////////////////////////////////////////////////////////////////////////////////
//��˹ƽ��������ģ��Ϊ[1,2,1]*[1,2,1]'
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsGaussSmooth(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_dst, 		//�����ƽ�����ͼ��
		unsigned char *img_8u1_temp);		//ͼ�񻺴�
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ֵƽ��������ƽ������Ĵ�СΪ��w0*h0�����ڴ�СΪ3*3����400*400����С��img_width,img_height
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsMeanSmooth(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int w0,						//ƽ��������
		const int h0,						//ƽ������߶�
		unsigned char *img_8u1_dst,			//�����ƽ�����ͼ��
		unsigned char *img_8u1_buffer);		//ͼ�񻺴�
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ȡsobel�ݶȷ���ͼ����
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsSobelMag(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_mag, 		//������ݶȷ���ͼ��
		unsigned char *table_sobel_sqrt);	//sobel��ƽ�����ұ��棬��С����Ϊ136900
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ȡsobel�ݶȷ��ȡ��ݶȷ���ͼ�����������ݶȷ�������ֵ��2=�Ƕ�ֵ����90����180�ȣ�30����60�ȡ�����
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsSobelMagOri(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_mag, 		//������ݶȷ���ͼ��
		unsigned char *img_8u1_ori, 		//������ݶȷ���ͼ��
		unsigned char *table_sobel_sqrt);	//sobel��ƽ�����ұ��棬��С����Ϊ136900
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ȡ����ͼ��Ŀռ�������ͼ�񣬼�ÿһ�����ص�����ھֲ������������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsSpatialSaliency(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int scale_x,					//��ע�ĳ߶ȴ�С,x���򣬴����ע��Ŀ����Ϊscale_x
		const int scale_y,					//��ע�ĳ߶ȴ�С,y���򣬴����ע��Ŀ��߶�Ϊscale_y
		unsigned char *img_8u1_saliency, 	//�����������ͼ��
		unsigned char *img_8u1_temp1, 		//����ͼ��
		unsigned char *img_8u1_temp2,		//����ͼ��
		int *img_32u1_temp);				//���������ֵ�Ļ���ͼ�񣬴�СΪimg_width*img_height*sizeof(int)
		
/////////////////////////////////////////////////////////////////////////////////////////
//������̬ѧ��ñ����õ���Ŀ��Ĳв�ͼ��Ŀ�������ΧԽ���в�ֵԽ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsTopHat(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int scale_x,					//��ע�ĳ߶ȴ�С,x���򣬴����ע��Ŀ����Ϊscale_x�����ǵ�Ч��ȡֵ3-5����
		const int scale_y,					//��ע�ĳ߶ȴ�С,y���򣬴����ע��Ŀ��߶�Ϊscale_y�����ǵ�Ч��ȡֵ3-5����
		unsigned char *img_8u1_residual); 	//����Ĳв�ͼ��
		
/////////////////////////////////////////////////////////////////////////////////////////
//������̬ѧ��ñ����õ���Ŀ��Ĳв�ͼ��Ŀ�������ΧԽ���в�ֵԽ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBottomHat(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int scale_x,					//��ע�ĳ߶ȴ�С,x���򣬴����ע��Ŀ����Ϊscale_x�����ǵ�Ч��ȡֵ3-5����
		const int scale_y,					//��ע�ĳ߶ȴ�С,y���򣬴����ע��Ŀ��߶�Ϊscale_y�����ǵ�Ч��ȡֵ3-5����
		unsigned char *img_8u1_residual); 	//����Ĳв�ͼ��
	
/////////////////////////////////////////////////////////////////////////////////////////
//��ֵ�ָ��ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsSegmentThd(
		const unsigned char *img_8u1_src, 	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int thd,						//�ָ���ֵ
		const int object_mode,				//��ע��Ŀ��ʱ��ֵ1����ע��Ŀ��ʱ��ֵ0
		unsigned char *img_8u1_binary); 	//����Ķ�ֵͼ��
		
/////////////////////////////////////////////////////////////////////////////////////////
//���ù��ҷ���ȡ����Ӧ��ֵ��ͨ�����ڲв�ͼ��������ͼ��ֱ��ͼ���е����ͼ�����ֵ�ָ�
//�ο����ף�Unimodal thresholding, Pattern Recognition, 2001
//����ֵ����ȡ�ķָ���ֵ
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsTriangularThreshold(
		const int *hist, 					//ͼ��ĻҶ�ֱ��ͼ
		const float exp_ratio); 			//����ֱ��ͼ�Աȶȵ���ָ��
	
/////////////////////////////////////////////////////////////////////////////////////////
//���û��ڹ��������ISODATA������ȡ����Ӧ��ֵ��ͨ������ֱ��ͼ����˫������ͼ�����ֵ�ָ�
//�ο����ף�Supervised grayscale thresholding based on transition regions, Image and Vision Computing, 2008
//����ֵ����ȡ�ķָ���ֵ
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsIsodataThreshold(
		const int *hist, 					//ͼ��ĻҶ�ֱ��ͼ
		const float min_ratio_low,			//�޶����ڵ������������С����
		const float min_ratio_high); 		//�޶����ڸ������������С����
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ֵͼ�����̬ѧ��ʴ��������ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryErose(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_dst); 		//����Ķ�ֵͼ��

/////////////////////////////////////////////////////////////////////////////////////////
//��ֵͼ�����̬ѧ���Ͳ�������ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryDilate(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_dst); 		//����Ķ�ֵͼ��
		
/////////////////////////////////////////////////////////////////////////////////////////
//��ֵͼ�����̬ѧ�����������������ȥ����������ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryOpen(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int noise_level,				//������Σ���ʾһ��������noise_level�θ�ʴ��noise_level������
		unsigned char *img_8u1_dst, 		//����Ķ�ֵͼ��
		unsigned char *img_8u1_buffer); 	//ͼ�񻺴�

/////////////////////////////////////////////////////////////////////////////////////////
//��ֵͼ�����̬ѧ��������������������С�ס���ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryClose(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int hole_level,				//С�ײ�Σ���ʾһ��������hole_level�����͡�hole_level�θ�ʴ
		unsigned char *img_8u1_dst, 		//����Ķ�ֵͼ��
		unsigned char *img_8u1_buffer); 	//ͼ�񻺴�
		
/////////////////////////////////////////////////////////////////////////////////////////
//�õ���ֵͼ������Ե����ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryExternalEdge(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_dst); 		//����ı�Եͼ��
		
/////////////////////////////////////////////////////////////////////////////////////////
//�õ���ֵͼ����ڱ�Ե����ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsBinaryInternalEdge(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		unsigned char *img_8u1_dst); 		//����ı�Եͼ��

/////////////////////////////////////////////////////////////////////////////////////////
//�ߴ��˲�����ȥ����ֵͼ�������̫������̫С����ͨ���򡣶�ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
void qsSizeFilter(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_size,					//��������ͨ�������С�������������
		const int max_size,					//��������ͨ���������������������
		unsigned char *img_8u1_dst,			//����ľ����ߴ��˲���Ķ�ֵͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//��ͨ�ɷַ�����Connected Component Analysis�����õ���ֵͼ������ͨ����������ο������
//����ֵ������Ҫ�����ͨ����ĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsCCA(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_size,					//�޶�����ͨ�������С�������������
		const int max_size,					//�޶�����ͨ���������������������
		const int max_object_num,			//�޶�����ͨ������������
		QSRECT	rc[],						//�������ͨ�������Ӿ��ο�
		int size[],							//�������ͨ������������������
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)
		

//�����ʽṹ��		
typedef struct
{
	//����λ��
	int						x, y;
	//HOG��������
	unsigned char			descriptor_HOG[45];
}QsFeatureCode;

//ƥ��Խṹ��
typedef struct
{
	//�ο�ͼ�����������λ��
	int						ref_x, ref_y;
	//��Ӧ�ĵ�ǰͼ�����������λ��
	int						real_x, real_y;
	//ƥ�����
	float error;
} QsMatchPair;

/////////////////////////////////////////////////////////////////////////////////////////
//FAST������ȡ����������ȡ���������ܼ����ʺ���Ŀ��ʶ��
//����ֵ���������������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsFeatureDetectFast(
		const unsigned char *img_8u1_src,	//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const int similar_thd,				//��ȡfast������ʱ�ж������������ֵ
		const int mx_feature_num,			//�޶�������������������������������ǵ���Ӧֵ����mx_feature_num���ǵ�
		const int descriptor_rotation_flag,	//�����������Ƿ���Ҫ������ת�����ԣ���ֵ0��ʾ����Ҫ������ֵ������Ҫ��ת������
		unsigned char *img_8u1_responce,	//ͼ�񻺴棬���ڴ洢FAST��Ӧֵ
		QsFeatureCode features[]);			//���������λ�á�����HOG��������	
		
/////////////////////////////////////////////////////////////////////////////////////////
//FAST������ȡ����������ȡ��������ϡ�衢�ҿռ�ֲ��Ͼ��ȣ��ʺ���ͼ��ƥ��
//����ֵ���������������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsFeatureDetectFastSparse(
		const unsigned char *img_8u1_src,	//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const int similar_thd,				//��ȡfast������ʱ�ж������������ֵ
		const int mx_feature_num,			//�޶�������������������������������ǵ���Ӧֵ����mx_feature_num���ǵ�
		const int descriptor_rotation_flag,	//�����������Ƿ���Ҫ������ת�����ԣ���ֵ0��ʾ����Ҫ������ֵ������Ҫ��ת������
		unsigned char *img_8u1_responce,	//ͼ�񻺴棬���ڴ洢FAST��Ӧֵ
		QsFeatureCode features[]);			//���������λ�á�����HOG��������

/////////////////////////////////////////////////////////////////////////////////////////
//����KL�����HOG����������ƥ��
//����ֵ�����ƥ���Ե�����
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsFeatureMatchHog(
		const QsFeatureCode feature_ref[], 	//��׼ͼ���е������㼯
		const int num_ref, 					//��׼ͼ���е�����������
		const QsFeatureCode feature_real[], //��ǰͼ���е������㼯
		const int num_real, 				//��ǰͼ���е�����������
		const int max_displacement,			//�������������Լ�ľ���
		int *dis_matrix,					//������󻺴棬��С��С��num_basic*num_real
		QsMatchPair match_pairs[]);			//�����ƥ���������
	
/////////////////////////////////////////////////////////////////////////////////////////
//������С���˷�(LSE)��ƥ��Եķ���任����
//      x_ref = p0 * x_real + p1 * y_real + p2
//      y_ref = p3 * x_real + p4 * y_real + p5
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsFeatureTransformParaLse(
		const QsMatchPair match_points[],	//ƥ���������
		const int match_num,				//ƥ��������Ե�����
		float affine_para[]);				//����ķ���任����
	
/////////////////////////////////////////////////////////////////////////////////////////
//����RANSAC��ƥ��Եķ���任����
//      x_ref = p0 * x_real + p1 * y_real + p2
//      y_ref = p3 * x_real + p4 * y_real + p5
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsFeatureTransformParaRansac(
		const QsMatchPair match_points[],	//ƥ���������
		const int match_num,				//ƥ��������Ե�����
		const int ransac_num,				//����ransac�Ĵ���
		float affine_para[]);				//����ķ���任����

/////////////////////////////////////////////////////////////////////////////////////////
//����RANSAC��ƥ��Եķ���任����
//		affine_para_src = [p0, p1, p2, p3, p4, p5],  affine_para_inverse = [q0, q1, q2, q3, q4, q5]
//      x_ref = p0 * x_real + p1 * y_real + p2,		y_ref = p3 * x_real + p4 * y_real + p5
//      x_real = q0 * x_ref + q1 * y_ref + q2,      y_real = q3 * x_ref + q4 * y_ref + q5
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
void qsFeatureTransformParaInverse(
		const float affine_para_src[],		//����ķ���任����
		float affine_para_inverse[]);		//����ķ���任����

/////////////////////////////////////////////////////////////////////////////////////////
//���ڷ���任����������ͼ��Ĳв�ͼ��
//      x_ref = p0 * x_real + p1 * y_real + p2
//      y_ref = p3 * x_real + p4 * y_real + p5
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////			
void qsFrameDifferenceAffine(
		const unsigned char *img_8u1__real, //��ǰʱ��ͼ������
		const unsigned char *img_8u1_ref, 	//��׼ͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const float *affine_para, 			//����任����
		unsigned char *img_8u1_diff);		//����Ĳв�ͼ������






/////////////////////////////////////////////////////////////////////////////////////////
//����������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsObjectTrackStart(
		const unsigned char *img_8u3_src,	//��ʼ֡ͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSRECT rc_init);				//��ʼ��Ŀ�����ڵķ�Χ

/////////////////////////////////////////////////////////////////////////////////////////
//�ڵ�ǰ֡ͼ����ִ�и�����
//����ֵ����ǰͼ����Ŀ�����Ӿ��ο�λ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
QSRECT qsObjectTrackExcute(
		unsigned char *img_8u3_src,			//��ǰ֡ͼ������
		const int img_width,				//ͼ����
		const int img_height);				//ͼ��߶�

/////////////////////////////////////////////////////////////////////////////////////////
//ֹͣ������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsObjectTrackStop();





//Բ����, ����Ϊ(x-x0)^2 +  (y-y0)^2 = r^2
typedef struct
{
	float 	x, y;							//���ĵ�
	float 	r;								//�뾶
}QSCIRCLE;

/////////////////////////////////////////////////////////////////////////////////////////
//����һ��Բ����
//����ֵ��������Բ����
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
QSCIRCLE qsCircleCreate(
		const float x,						//Բ���ĵ��x����
		const float y,						//Բ���ĵ��y����
		const float r);						//Բ�뾶

/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ��Բ
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddCircleToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSCIRCLE circle,				//Բ����
		const int line_thick,				//Բ�����Ŀ��
		const int r, 						//Ҫ��ӵ�Բ��������ɫ-red
		const int g, 						//Ҫ��ӵ�Բ��������ɫ-green
		const int b);						//Ҫ��ӵ�Բ��������ɫ-blue

/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ��ʵ��Բ
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddHardCircleToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSCIRCLE circle,				//Բ����
		const int r, 						//Ҫ��ӵ�ʵ��Բ����ɫ-red
		const int g, 						//Ҫ��ӵ�ʵ��Բ����ɫ-green
		const int b,						//Ҫ��ӵ�ʵ��Բ����ɫ-blue
		const float alfa);					//��ɫ������ӻ�͸����, 0-1,1��ʾȫ����	

/////////////////////////////////////////////////////////////////////////////////////////
//�õ�Բ�Ĳ����޶��Ķ�ֵͼ�����򣬶�ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsCircleArea(
		unsigned char *img_8u1_binary,		//����Ķ�ֵͼ��
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSCIRCLE circle);				//Բ����

/////////////////////////////////////////////////////////////////////////////////////////
//�õ�����Բ�Ĳ����޶��Ļ��εĶ�ֵͼ�����򣬶�ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsCircleRaceArea(
		unsigned char *img_8u1_binary,		//����Ķ�ֵͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSCIRCLE circle1,				//Բ1����
		const QSCIRCLE circle2);			//Բ2����

/////////////////////////////////////////////////////////////////////////////////////////
//������С���˷�(LSE)��Բ�Ĳ���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsCircleParaLse(
		const int x_point[],				//Բ�����ص��x����
		const int y_point[],				//Բ�����ص��y����
		const int num_point,				//Բ�����ص������
		QSCIRCLE *circle);					//�����Բ�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//����ȥ1����Բ�Ĳ���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsCircleParaRobust(
		const int x_point[],				//Բ�����ص��x����
		const int y_point[],				//Բ�����ص��y����
		const int num_point,				//Բ�����ص������
		const float outlier_ratio,			//��Ҫȥ���Ļ���ı���[0, 0.5]
		QSCIRCLE *circle);					//�����Բ�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//�Ӷ�ֵͼ����ֵ�ָ�ͼ������Բ
//����ֵ��Բ�ĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsCircleFromBinaryImg(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_radius,				//�޶���Բ����С�뾶����������
		const int max_radius,				//�޶���Բ�����뾶����������
		const int max_circle_num,			//�޶���Բ���������
		const float max_bias_ratio,			//�޶�Բ���ϵĵ�����ƫ�������ֵ�����ֵ�����ƫ�����/�뾶��0.01-0.2��
		QSCIRCLE circles[],					//�����Բ�Ĳ���
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//�ӻҶ�ͼ����ֱ����ȡԲ��������Ŀ��ͼ��̫���׽��ж�ֵ�ָ�ĳ���
//ֱ�ӴӻҶ�ͼ����Ч�ʽϵͣ���Ч��Ҳ��һ���ã������ܽ��ж�ֵ�ָ�ľ�����취�ָ�
//����ֵ��Բ�ĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsCircleFromGrayImg(
		const unsigned char *img_8u1_gray,	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_radius,				//�޶���Բ����С�뾶����������
		const int max_radius,				//�޶���Բ�����뾶����������
		const int max_circle_num,			//�޶���Բ���������
		const float max_bias_ratio,			//�޶�Բ���ϵĵ�����ƫ�������ֵ�����ֵ�����ƫ�����/�뾶��0.01-0.2��
		QSCIRCLE circles[],					//�����Բ�Ĳ���
		unsigned char *img_8u1_edge,		//����ı�Եͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴棬��СΪ136900��img_width*img_height�����ֵ
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//������Բ�����޶��Ļ���ͼ���������죬�õ����εĳ�������
//���ڹ����ϵ��ַ��ǰ���˳ʱ�����еģ�������췽��Ϊ˳ʱ��
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsCircleRaceStretchImg(
		const unsigned char *img_8u1_gray,	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const QSCIRCLE circle_out,			//��Բ����
		const QSCIRCLE circle_in,			//��Բ����
		int *stretched_img_width,			//�����������ͼ��Ŀ�ȣ�Բ�ܷ��򣩣� (circle_out.r * 2 * QS_PI)
		int *stretched_img_height,			//�����������ͼ��ĸ߶ȣ��뾶���򣩣�(circle_out.r - circle_in.r)
		unsigned char *img_8u1_stretched);	//����Ĵ�СΪstretched_img_width*stretched_img_height��������ͼ��


//��Բ������Բ�������Բ��������˶���/�����ӳ���ʱ����Ϊ��Բ
//����Ϊ[(x-x0)cos(sita)+(y-y0)sin(sita)]^2        [-(x-x0)sin(sita)+(y-y0)cos(sita)]^2
//      -----------------------------------    +   ------------------------------------   =  1
//                     rx^2                                          ry^2
typedef struct
{
	float 	x, y;							//���ĵ�
	float 	rx;								//����
	float	ry;								//����
	float	sita;							//rx��x���ߵļн�,��λΪ����[0, 2*QS_PI)
}QSELLIPSE;

/////////////////////////////////////////////////////////////////////////////////////////
//����һ����Բ����
//����ֵ����������Բ����
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
QSELLIPSE qsEllipseCreate(
		const float x,						//��Բ���ĵ��x����
		const float y,						//��Բ���ĵ��y����
		const float rx,						//��Բx�������ĳ��ȵ�һ��
		const float ry,						//��Բy�������ĳ��ȵ�һ��
		const float sita);					//rx��x���ߵļн�,��λΪ�Ƕ�

/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ����Բ
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddEllipseToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		QSELLIPSE ellipse,					//��Բ����
		const int line_thick,				//�����Ŀ��
		const int r, 						//Ҫ��ӵ�Բ��������ɫ-red
		const int g, 						//Ҫ��ӵ�Բ��������ɫ-green
		const int b);						//Ҫ��ӵ�Բ��������ɫ-blue

/////////////////////////////////////////////////////////////////////////////////////////
//�õ���Բ�Ĳ����޶��Ķ�ֵͼ�����򣬶�ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsEllipseArea(
		unsigned char *img_8u1_binary,		//����Ķ�ֵͼ��
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		QSELLIPSE ellipse);					//��Բ�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//�õ�������Բ�Ĳ����޶����ֻ��εĶ�ֵͼ�����򣬶�ֵͼ����ǰ��Ϊ255������Ϊ0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void qsEllipseRaceArea(
		unsigned char *img_8u1_binary,		//����Ķ�ֵͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		QSELLIPSE ellipse1,					//��Բ1�Ĳ���
		QSELLIPSE ellipse2);				//��Բ2�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//������С���˷�(LSE)����Բ�Ĳ���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsEllipseParaLse(
		const int x_point[],				//��Բ�����ص��x����
		const int y_point[],				//��Բ�����ص��y����
		const int num_point,				//��Բ�����ص������
		QSELLIPSE *ellipse);				//�������Բ�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//����ȥ1������Բ�Ĳ���
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int qsEllipseParaRobust(
		const int x_point[],				//��Բ�����ص��x����
		const int y_point[],				//��Բ�����ص��y����
		const int num_point,				//��Բ�����ص������
		const float outlier_ratio,			//��Ҫȥ���Ļ���ı���[0, 0.5]
		QSELLIPSE *ellipse);				//�������Բ�Ĳ���

/////////////////////////////////////////////////////////////////////////////////////////
//�Ӷ�ֵͼ����ֵ�ָ�ͼ��������Բ
//����ֵ����Բ�ĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsEllipseFromBinaryImg(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_radius,				//�޶�����Բ����С�뾶(rx+ry/2)����������
		const int max_radius,				//�޶�����Բ�����뾶(rx+ry/2)����������
		const int max_ellipse_num,			//�޶�����Բ���������
		const float max_bias_ratio,			//�޶���Բ���ϵĵ�����ƫ�������ֵ�����ֵ�����ƫ�����/�����ᣬ0.01-0.2��
		QSELLIPSE ellipses[],				//�������Բ�Ĳ���
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//�ӻҶ�ͼ����ֱ����ȡ��Բ��������Ŀ��ͼ��̫���׽��ж�ֵ�ָ�ĳ���
//ֱ�ӴӻҶ�ͼ����Ч�ʽϵͣ���Ч��Ҳ��һ���ã������ܽ��ж�ֵ�ָ�ľ�����취�ָ�
//����ֵ��Բ�ĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsEllipseFromGrayImg(
		const unsigned char *img_8u1_gray,	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_radius,				//�޶�����Բ����С�뾶(rx+ry/2)����������
		const int max_radius,				//�޶�����Բ�����뾶(rx+ry/2)����������
		const int max_ellipse_num,			//�޶�����Բ���������
		const float max_bias_ratio,			//�޶���Բ���ϵĵ�����ƫ�������ֵ�����ֵ�����ƫ�����/�����ᣬ0.01-0.2��
		QSELLIPSE ellipses[],				//�������Բ�Ĳ���
		unsigned char *img_8u1_edge,		//����ı�Եͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴棬��СΪ136900��img_width*img_height�����ֵ
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//��������Բ�����޶��Ļ���ͼ���������죬�õ����εĳ�������
//���ڹ����ϵ��ַ��ǰ���˳ʱ�����еģ�������췽��Ϊ˳ʱ��
//����ֵ���ɹ�����RETURN_SUCESS��ʧ�ܷ���RETURN_FAILURE
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsEllipseRaceStretchImg(
		const unsigned char *img_8u1_gray,	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const QSELLIPSE ellipse_out,		//����Բ����
		const QSELLIPSE ellipse_in,			//����Բ����
		int *stretched_img_width,			//�����������ͼ��Ŀ�ȣ�Բ�ܷ��򣩣� (ellipse_out.rx+ ellipse_out.ry) * QS_PI
		int *stretched_img_height,			//�����������ͼ��ĸ߶ȣ��뾶���򣩣�(ellipse_out.rx+ellipse_out.ry - ellipse_in.rx-ellipse_in.ry)/2
		unsigned char *img_8u1_stretched);	//����Ĵ�СΪstretched_img_width*stretched_img_height��������ͼ��







											
//�߶ζ���
typedef struct
{
	float 	x1;								//���Ƶ�1��x����
	float 	y1;								//���Ƶ�1��y����
	float 	x2;								//���Ƶ�2��x����
	float 	y2;								//���Ƶ�2��y����
}QSLINE;											

/////////////////////////////////////////////////////////////////////////////////////////
//����һ���߶ζ���
//����ֵ���������߶ζ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
QSLINE qsLineCreate(
		float 	x1,							//���Ƶ�1��x����
		float 	y1,							//���Ƶ�1��y����
		float 	x2,							//���Ƶ�2��x����
		float 	y2);						//���Ƶ�2��y����

/////////////////////////////////////////////////////////////////////////////////////////
//����߶ζ���ĳ��ȣ�������
//����ֵ���߶εĳ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
float qsLineLength(QSLINE line);

/////////////////////////////////////////////////////////////////////////////////////////
//��ͼ�������һ���߶�
//Author��EmbedVison
/////////////////////////////////////////////////////////////////////////////////////////
void qsAddLineToImg(
		unsigned char *img_8u3_src,			//����Դͼ������
		const int img_width,				//ͼ����
		const int img_height,				//ͼ��߶�
		const QSLINE line,					//�߶ζ���
		const int line_thick,				//�������
		const int r, 						//Ҫ��ӵ��߶ε���ɫ-red
		const int g, 						//Ҫ��ӵ��߶ε���ɫ-green
		const int b);						//Ҫ��ӵ��߶ε���ɫ-blue

/////////////////////////////////////////////////////////////////////////////////////////
//�Ӷ�ֵͼ����ֵ�ָ�ͼ�������߶�
//����ֵ���߶εĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsLineFromBinaryImg(
		const unsigned char *img_8u1_binary, //����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_length,				//�޶����߶ε���С���ȣ���������
		const float error_bound,			//�߶��ϵĵ�ƫ��ֱ�ߵ�����Ͻ磬��λΪ����
		const int max_line_num,				//�޶����߶ε��������
		QSLINE lines[],						//������߶εĲ���
		unsigned char *img_8u1_buf,			//ͼ�񻺴�
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)

/////////////////////////////////////////////////////////////////////////////////////////
//�ӻҶ�ͼ����ֱ����ȡ�߶Σ�������Ŀ��ͼ��̫���׽��ж�ֵ�ָ�ĳ���
//ֱ�ӴӻҶ�ͼ����Ч�ʽϵͣ���Ч��Ҳ��һ���ã������ܽ��ж�ֵ�ָ�ľ�����취�ָ�
//����ֵ���߶εĸ���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////		
int qsLineFromGrayImg(
		const unsigned char *img_8u1_gray,	//����Դͼ������
		const int img_width, 				//ͼ����
		const int img_height, 				//ͼ��߶�
		const int min_length,				//�޶����߶ε���С���ȣ���������
		const float error_bound,			//�߶��ϵĵ�ƫ��ֱ�ߵ�����Ͻ磬��λΪ����
		const int max_line_num,				//�޶����߶ε��������
		QSLINE lines[],						//������߶εĲ���
		unsigned char *img_8u1_edge,		//����ı�Եͼ��
		unsigned char *img_8u1_buf,			//ͼ�񻺴棬��СΪ136900��img_width*img_height�����ֵ
		int *pt_object,						//���棬��СΪimg_width*img_height*sizeof(int)
		int *pt_stack);						//���棬��СΪimg_width*img_height*sizeof(int)



#ifdef __cplusplus
}
#endif


#endif
