#ifndef _ILLUMINATION_H
#define _ILLUMINATION_H

#include"stc12c5a60s2.h"
#include"delay.h"
//宏定义
#define	  SlaveAdd   0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A

typedef unsigned char BYTE;
typedef unsigned int  WORD; 
//引脚定义
sbit	  SCL = P2^2;      //IIC时钟引脚定义
sbit  	  SDA = P2^1;      //IIC数据引脚定义

//函数的声明
extern void  Init_guangzhao(void);
extern void  Write_guangzhao(uchar Address);                //单个写入数据
//extern uchar Single_Read_BH1750(uchar Address);                 //单个读取内部寄存器数据
extern void  read_BH1750_data(uchar Data[]);                     //连续的读取内部寄存器数据
extern void  guangzhao_Start();                                        //起始信号
extern void  guangzhao_Stop();                                         //停止信号
extern void  guangzhao_SendACK(bit ack);                               //应答ACK
extern bit   BH1750_RecvACK();                                      //读ack
extern void  BH1750_SendByte(BYTE dat);                             //IIC单个字节写
extern BYTE  RecvByte();                                     //IIC单个字节读
extern uint Get_guangzhao(void);									 //获取光照的数据

#endif
