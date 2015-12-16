/////////////////////////////////////////////////////////////////////////////////////////
//V4L2.h
//����V4L2Э���������Ľӿں���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef		__V4L2_H__
#define		__V4L2_H__

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

//ͼ���Ⱥ͸߶�
#define IMAGE_WIDTH						640	
#define IMAGE_HEIGHT					480

#ifdef __cplusplus
extern "C" {
#endif

//ͼ�񻺳����ṹ��
typedef	struct
{
	void				*start;					//��ʼ��ַ
	size_t				length;					//��������С
}image_buffer;

//����V4L2Э������������Ľṹ��
typedef	struct
{
	//�û���������
	char				*dev_name;				//�豸����/dev/vidio*
	
	//�Լ�����ı���������
	int					fd;						//�豸���
	int					n_buffers;				//��Ƶ������������
	image_buffer		*buffers;				//ͼ�񻺳����ĵ�ַ
	int					frame_index;			//�ɼ�����֡�����
	int					failure_count;			//�����ɼ�ʧ�ܵĴ���,�������ж�����Ƿ����
}V4L2_data;

/////////////////////////////////////////////////////////////////////////////////////////
//�򿪲���ʼ������ͷ�豸��������Ƶ�ɼ�
//�򿪳ɹ�����1����ʧ�ܷ���С��0�Ĵ������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_dev (V4L2_data *camera);

/////////////////////////////////////////////////////////////////////////////////////////
//ֹͣ����ͷ�豸
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void stop_dev (V4L2_data *camera);

/////////////////////////////////////////////////////////////////////////////////////////
//��ȡ֡ͼ��
//��ȡ�ɹ�����1����ȡʧ�ܷ���0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int read_frame(V4L2_data *camera, 
				unsigned char *img_8u3_rgb888, 				/*�����RGB888����*/
				unsigned char *img_8u1_gray = NULL);		/*����ĻҶ�ͼ������*/


#ifdef __cplusplus
}
#endif


#endif
