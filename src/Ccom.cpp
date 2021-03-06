#include "Ccom.h"

Com::Com()
{
	_fd=-1;
}
Com::Com(char * file_name)
{
	init(file_name);
}
void Com::init(char * file_name)
{
	if(_fd != -1)
	{
		_fd=UART0_open(file_name);
		if(_fd == -1)
		{
			std::cerr<<"open serial port failed\n";
		}
	}
}
void Com::close()
{
	UART0_close(_fd);
}
void Com::set(int baud,int flow_ctrl,int databits,int stopbits,int parity)
{
	if(_fd != -1)
	{
		if(UART0_set(_fd,baud,flow_ctrl,databits,stopbits,parity) != -1)
		{
			_baud=baud;
			_flow_ctrl=flow_ctrl;
			_databits=databits;
			_stopbits=stopbits;
			_parity=parity;
		}
	}
	else
	{
		std::cerr<<"Can not find port\n";
	}
}
void Com::send(int x,int y)
{
	//send_buffer
	//低位在前，高位在后 x,y
	send_buffer[0]=x & 0x000000ff;
	send_buffer[1]=(x>>8) & 0x000000ff;
	send_buffer[2]=(x>>8) & 0x000000ff;
	send_buffer[3]=(x>>8) & 0x000000ff;

	send_buffer[4]=y & 0x000000ff;
	send_buffer[5]=(y>>8) & 0x000000ff;
	send_buffer[6]=(y>>8) & 0x000000ff;
	send_buffer[7]=(y>>8) & 0x000000ff;

	UART0_send(_fd,send_buffer,8);
}
int Com::receive(char * rcv_buffer)
{
    return 0;
}
Com::~Com()
{
    UART0_close(_fd);
}