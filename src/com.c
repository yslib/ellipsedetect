

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/


int UART0_open(char * file_name)
{
	/*
	*
	*/
	int fd=open(file_name,O_RDWR|O_NOCTTY|O_NDELAY);

	if(fd == -1)
	{
		fprintf(stderr, "open serial port failed\n");
		return -1;
	}
	else
	{
		fcntl(fd,F_SETFL,0);
		return fd;
	}

}
int UART0_close(int fd)
{
	close(fd);
}
int UART0_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{
	struct termios settings;

	int speeds[]={B57600,B76800,B115200,B38400,B19200,B9600,B4800,B2400,B1200,B300};
	/*
	*获取串口属性
	*/
	if(tcgetattr(fd,&settings) != 0)
	{
		/*获取串口参数失败*/
		fprintf(stderr, "get serial port options failed\n");
		return -1;
	}
	/*
	*设置波特率
	*/
	for(int i=0;i<sizeof(speeds)/sizeof(int);i++)
	{
		if(speed == speeds[i])
		{
			cfsetispeed(&settings,speeds[i]);
			cfsetispeed(&settings,speeds[i]);
		}
	}
	/*
	*设置属性
	*CLOAL:保证程序不会占用串口
	*CREAD:能从串口中读取数据
	*/
	settings.c_cflag|=(CLOCAL|CREAD);

	/*设置数据位*/
	settings.c_cflag|=~CSIZE;		//位屏蔽
	switch(databits)
	{
		case UART_DATABIT5:
		settings.c_cflag|=CS5;
		break;
		case UART_DATABIT6:
		settings.c_cflag|=CS6;
		break;
		case UART_DATABIT7:
		settings.c_cflag|=CS7;
		break;
		case UART_DATABIT8:
		settings.c_cflag|=CS8;
		break;
		default:
		fprintf(stderr, "data bit option error\n");
		return -1;
	}
	/*
	*设置奇偶校验
	*/
	switch(parity)
	{
		case UART_PARITY_NON:			//无校验
		settings.c_cflag &=~PARENB;
		settings.c_iflag &=~INPCK;
		break;

		case UART_PARITY_ODD:			//奇校验
		settings.c_cflag |=PARENB;
		settings.c_cflag |=PAROOD;
		settings.c_iflag |=INPCK;
		break;

		case UART_PARITY_EVE:			//偶校验
		settings.c_cflag |=PARENB;
		settings.c_cflag &=~PAROOD;
		settings.c_iflag |=INPCK;

		case UART_PARITY_SPA:			//空格校验
		settings.c_cflag &=~PARENB;
		settings.c_cflag &=~CSTOPB;
		break;
		default:
		fprintf(stderr, "parity bit option error\n");
		return -1;
	}

	/*
	*设置停止位
	*/
	switch(stopbits)
	{
		case UART_STOPBIT0:
		settings.c_cflag &= ~CSTOPB;
		break;
		case UART_STOPBIT1:
		settings.c_cflag |=CSTOPB;
		break;
		default:
		fprintf(stderr, "stop bit option error.\n");
		return -1;
	}

	/*
	*设置数据流控制
	*/
	switch(flow_ctrl)
	{
		case UART_FLOWCTRL_NON:
		settings.c_cflag &=~CRTSCTS;			//不使用
		break;
		case UART_FLOWCTRL_HAR:
		settings.c_cflag |= CRTSCTS;		//硬件流控制
		break;
		case UART_FLOWCTRL_SOF:
		settings.c_cflag |=IXON|IXOFF|IXANY;		//软件流控制
		break;
	}

	//settings.c_lflag |= (ICANON | ECHO | ECHOE);		//原始输入


	settings.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*经典输入*/
	settings.c_oflag  &= ~OPOST;   /*原始输出*/

	/*读取数据等待时间和最小接收字符*/
	//settings.c_cc[VMIN]=1;
	//settings.c_cc[VTIME]=1;

	//tcflush(fd,TCIFULSH);

	//应用设置，立即生效
	if(tcsetattr(fd,TCSANOW,&settings) != 0)
	{
		fprintf(stderr, "com options set failed\n");
		return -1;
	}
	return 1;
}
//
//receive data
//
int UART0_receive(int fd,char * rcv_buffer,int data_len)
{
	
}
//
//send data
//
int UART0_send(int fd,char * send_buffer,int data_len)
{
	int len=0;
	len=write(fd,send_buffer,data_len);
	if(len == data_len)
	{
		return len;
	}
	else
	{
		tcflush(fd,TCOFLUSH);		//清除写入的数据
		return -1;
	}
}