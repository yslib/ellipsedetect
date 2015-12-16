/////////////////////////////////////////////////////////////////////////////////////////
//V4L2.cpp
//����V4L2Э���������Ľӿں���
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
#include "V4L2.h"
#include <stdio.h>

#define MAX_FAILURE_COUNT					20

/////////////////////////////////////////////////////////////////////////////////////////
//������ͷ�豸�ļ�
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int open_device(V4L2_data *camera)
{
	if (-1 == (camera->fd = open (camera->dev_name, O_RDWR | O_NONBLOCK, 0)))
		return -1;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//��ʼ������ͷ�豸
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_device(V4L2_data* camera)
{
	//��ѯ�豸�����Ĺ���
	v4l2_capability cap;
	if (-1 == ioctl (camera->fd, VIDIOC_QUERYCAP, &cap))
		return -11;
	//����֧����Ƶ���������˳�
	if (! (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
		return -12;
	if (! (cap.capabilities & V4L2_CAP_STREAMING))
		return -13;
		
	//������Ƶ�豸����Ƶ���ݸ�ʽ
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
//������Ƶ������
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_mmap(V4L2_data *camera)
{
	//����V4L2����������Ƶ������������V4L2��Ƶ���������ڴ棩
	v4l2_requestbuffers req;
	memset(&req, 0, sizeof(v4l2_requestbuffers));
	req.count	=	2;									//����Ļ������ĸ���
	req.type	=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory	=	V4L2_MEMORY_MMAP;					//mmap��ʽ
	if(-1 == ioctl (camera->fd, VIDIOC_REQBUFS, &req))
		return -21;
	//��ֻ���뵽1����û�����뵽���������򷵻�
	if(req.count < 2)
		return -22;

	//���ں˿ռ��ַӳ�䵽�û��ռ䣬����Ӧ�ó���ķ���
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
			
		//Ͷ�ſյ���Ƶ����������Ƶ���������������
		if (-1 == ioctl (camera->fd, VIDIOC_QBUF, &v4l2_buf))
			return -25;
	}
	
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//������Ƶ�ɼ�
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int start_capturing(V4L2_data *camera)
{
	//������Ƶ�ɼ�
	enum v4l2_buf_type type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl (camera->fd, VIDIOC_STREAMON, &type))
		return -31;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//�򿪲���ʼ������ͷ�豸��������Ƶ�ɼ�
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_dev (V4L2_data *camera)
{
	camera->failure_count = 0;
	camera->frame_index = 0;
	
	//������ͷ�豸
	int error_code = open_device(camera);
	if(error_code < 0 )
		return error_code;
	
	//���÷ֱ��ʵȲ���
	error_code = init_device(camera);
	if(error_code < 0 )
		return error_code;

	//���仺��
	error_code = init_mmap(camera);
	if(error_code < 0 )
		return error_code;

	//������Ƶ�ɼ�
	error_code = start_capturing(camera);
	if(error_code < 0 )
		return error_code;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
//ֹͣ����ͷ�豸
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void stop_dev (V4L2_data *camera)
{
	//ֹͣ��Ƶ�ɼ�
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl (camera->fd, VIDIOC_STREAMOFF, &type);

	//�ͷŷ���Ŀռ�
	for (int i = 0; i < camera->n_buffers; ++i)
		munmap(camera->buffers[i].start, camera->buffers[i].length);
	
	//�ر�����ͷ
	close(camera->fd);
}


/////////////////////////////////////////////////////////////////////////////////////////
//YUVתRGB����
//������img_8u2_yuyv��������ͼ��YUYV
//      img_8u3_rgb�������ͼ��RGB
//      img_width����ͼ����
//      img_height����ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void Yuv2Rgb(unsigned char *img_8u2_yuyv,
			unsigned char *img_8u3_rgb, 
			const int img_width, 
			const int img_height)
{
	int i;
	
	//YUVͼ��ĳߴ�
	int yuv_size = img_width * img_height * 2;
	
	//������ͼ�������е�ƫ����
	int offset_rgb = 0;
	int offset_yuv = 0;
	
	//YUYVֵ
	int y0, u, y1, v;
	//RGB����ֵ
	int delta_r, delta_g, delta_b;

	//�ضϲ��ұ��丳ֵ���޶����ֵ��ΧΪ[0,255]��������÷�ʽΪf(x)=table_cut[x+512]
	unsigned char table_cut[1024];
	for(i=0; i<512; i++)
		table_cut[i] = 0;
	for(i=512; i<768; i++)
		table_cut[i] = i-512;
	for(i=768; i<1024; i++)
		table_cut[i] = 255;

	//��ͼ���е�ÿһ��YUYVֵת��Ϊ2��RGBֵ
	for(offset_yuv = 0; offset_yuv < yuv_size; offset_yuv += 4) 
	{
		//�õ�YUYVֵ
		y0 = img_8u2_yuyv[offset_yuv] + 512;			//512Ϊ����0λ��
  		u  = img_8u2_yuyv[offset_yuv + 1] - 128;		//128Ϊɫ�ȵ�0λ��
  		y1 = img_8u2_yuyv[offset_yuv + 2] + 512;		//512Ϊ����0λ��
  		v  = img_8u2_yuyv[offset_yuv + 3] - 128;		//128Ϊ���Ͷȵ�0λ��
		
		//�õ�UV������ֵ
		delta_r = (351*v)>>8;                         	
		delta_g = -( (179*v + 86*u)>>8 );	
		delta_b = (444*u)>>8;

		//�õ�ת�����RGBֵ
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_r];
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_g];
		img_8u3_rgb[offset_rgb++] = table_cut[y0 + delta_b];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_r];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_g];
		img_8u3_rgb[offset_rgb++] = table_cut[y1 + delta_b];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//YUVתGray����
//������img_8u2_yuyv��������ͼ��YUYV
//      img_8u1_gray�������ͼ��Gray
//      img_width����ͼ����
//      img_height����ͼ��߶�
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
//������������ͷ�豸
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void restart_dev (V4L2_data *camera)
{
	//ֹͣ��Ƶ�ɼ�
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl (camera->fd, VIDIOC_STREAMOFF, &type);

	//�ͷŷ���Ŀռ�
	for (int i = 0; i < camera->n_buffers; ++i)
		munmap(camera->buffers[i].start, camera->buffers[i].length);
	
	//�ر�����ͷ
	close(camera->fd);
	
	//��������ͷ
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
//��ȡ֡ͼ��
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int read_frame(V4L2_data *camera, 
				unsigned char *img_8u3_rgb888, 				/*�����RGB888����*/
				unsigned char *img_8u1_gray)				/*����ĻҶ�ͼ������*/
{
	//��ǰ�������Ƶ���ݵĻ�����
	v4l2_buffer			current_buf;			
	memset(&current_buf, 0, sizeof(v4l2_buffer));
	current_buf.type	=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
	current_buf.memory	= 	V4L2_MEMORY_MMAP;
	ioctl (camera->fd, VIDIOC_DQBUF, &current_buf);
	
	//��������ַ
	unsigned char *img_buffer = (unsigned char *)(camera->buffers[current_buf.index].start);
	
	if(current_buf.bytesused != IMAGE_WIDTH*IMAGE_HEIGHT*2)
	{	
		//�ͷŵ�ǰ��ȡͼ��Ļ���
		printf("yuyv size Error! \n");
		camera->failure_count++;
		ioctl(camera->fd, VIDIOC_QBUF, &current_buf);
			
		//����γ���yuyv size Error��˵������ͷ�����˹��ϣ���������ͷ
		if(camera->failure_count > MAX_FAILURE_COUNT)
		{
			printf("yuyv capturing error, restart! \n");
			restart_dev(camera);
		}
		return 0;
	}
	camera->failure_count = 0;
	
	//ͼ���ʽת����YUV----RGB
	if(NULL != img_8u3_rgb888)
	{
		Yuv2Rgb(
			img_buffer, 
			img_8u3_rgb888, 
			IMAGE_WIDTH, 
			IMAGE_HEIGHT);
	}
	
	//ͼ���ʽת����YUV----GRAY
	if(NULL != img_8u1_gray)
	{
		Yuv2Gray(
			img_buffer, 
			img_8u1_gray, 
			IMAGE_WIDTH, 
			IMAGE_HEIGHT);
	}
	
	//�ͷŵ�ǰ��ȡͼ��Ļ���
	ioctl(camera->fd, VIDIOC_QBUF, &current_buf);
	
	camera->frame_index++;
	
	return 1;
}

