/////////////////////////////////////////////////////////////////////////////////////////
//V4L2.h
//符合V4L2协议的摄像机的接口函数
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

//图像宽度和高度
#define IMAGE_WIDTH						640	
#define IMAGE_HEIGHT					480

#ifdef __cplusplus
extern "C" {
#endif

//图像缓冲区结构体
typedef	struct
{
	void				*start;					//起始地址
	size_t				length;					//缓冲区大小
}image_buffer;

//符合V4L2协议的摄像机对象的结构体
typedef	struct
{
	//用户交互变量
	char				*dev_name;				//设备名称/dev/vidio*
	
	//自己管理的变量及缓存
	int					fd;						//设备句柄
	int					n_buffers;				//视频缓冲区的数量
	image_buffer		*buffers;				//图像缓冲区的地址
	int					frame_index;			//采集到的帧的序号
	int					failure_count;			//连续采集失败的次数,，用于判定相机是否故障
}V4L2_data;

/////////////////////////////////////////////////////////////////////////////////////////
//打开并初始化摄像头设备，启动视频采集
//打开成功返回1，打开失败返回小于0的错误代码
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int init_dev (V4L2_data *camera);

/////////////////////////////////////////////////////////////////////////////////////////
//停止摄像头设备
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
void stop_dev (V4L2_data *camera);

/////////////////////////////////////////////////////////////////////////////////////////
//读取帧图像
//读取成功返回1，读取失败返回0
//Author: EmbedVision
/////////////////////////////////////////////////////////////////////////////////////////
int read_frame(V4L2_data *camera, 
				unsigned char *img_8u3_rgb888, 				/*输出的RGB888数据*/
				unsigned char *img_8u1_gray = NULL);		/*输出的灰度图像数据*/


#ifdef __cplusplus
}
#endif


#endif
