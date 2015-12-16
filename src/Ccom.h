#ifndef _CCOM_H_
#define _CCOM_H_

#include "com.h"
#include <string>
#include <iostream>

class Com
{
private:
	int _fd;		//文件描述符
	int _baud;		//波特率
	std::string _file_name;
	int _flow_ctrl;
	int _databits;
	int _stopbits;
	int _parity;
	char  send_buffer[16];		//一次发送16字节数据，包括int x,int y,int hangle,int vangle
	char  rcv_buffer;
public:
	 Com();
	 Com(char * file_name);
	 void init(char * file_name);
	 void set(int baud,int flow_ctrl,int databits,int stopbits,int parity);
	 void send(int x,int y,int h_angle=-1,int v_hangle=-1);
	 int receive(char * rcv_buffer);
	 void close();
	~ Com();
    
	/* data */
};
#endif /*_CCOM_H_*/