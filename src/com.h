

#ifndef _COM_H_
#define _COM_H_

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/

#define UART_DATABIT5 5
#define UART_DATABIT6 6
#define UART_DATABIT7 7
#define UART_DATABIT8 8

#define UART_PARITY_NON 0
#define UART_PARITY_ODD	1
#define UART_PARITY_EVE	2
#define UART_PARITY_SPA 3

#define UART_STOPBIT0 0
#define UART_STOPBIT1 1

#define UART_FLOWCTRL_NON 0
#define UART_FLOWCTRL_HAR 1
#define UART_FLOWCTRL_SOF 2

/*
*打开串口
*/
int UART0_open(char * file_name);

/*
*关闭串口
*/
void UART0_close(int fd);

/*
*设置串口参数
*/
int UART0_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);

/*
*接收数据
*/
int UART0_receive(int fd,char * rcv_buffer,ssize_t data_len);

/*
*发送数据
*/
int UART0_send(int fd,char * send_buffer,ssize_t data_len);

#endif