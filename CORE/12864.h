#ifndef _12864_H_
#define _12864_H_

#include "stc12c5a60s2.h"
#include <intrins.h>

#ifndef uchar
#define  uchar unsigned char
#endif
#ifndef uint
#define  uint unsigned int
#endif

sbit LCD12864_RS=P2^5;    //并行的指令/数据选择信号, H数据, L命令
sbit LCD12864_RW=P2^6;    //并行读写选择信号, H读, L写
sbit LCD12864_EN=P2^7;    //并行使能端, H有效, L无效

#define LcdData P0

#define LCD12864_RS_L LCD12864_RS=0
#define LCD12864_RS_H LCD12864_RS=1
#define LCD12864_RW_L LCD12864_RW=0
#define LCD12864_RW_H LCD12864_RW=1
#define LCD12864_EN_L LCD12864_EN=0
#define LCD12864_EN_H LCD12864_EN=1

//基本指令集预定义
#define	LCD_CLEAR_SCREEN       	0x01 	 	//清屏	
#define	LCD_ADDRESS_RESET      	0x02		//地址归零	 
#define	LCD_BASIC_FUNCTION	  	0x30		//基本指令集
#define	LCD_EXTEND_FUNCTION	   	0x34		//扩充指令集
//扩展指令集预定义
#define	LCD_AWAIT_MODE			    0x01	 	//待命模式	
#define LCD_ROLLADDRESS_ON		  0x03		//允许输入垂直卷动地址
#define LCD_IRAMADDRESS_ON	   	0x02		//允许输入IRAM地址	
#define	LCD_SLEEP_MODE			    0x08	 	//进入睡眠模式
#define	LCD_NO_SLEEP_MODE	    	0x0c	 	//脱离睡眠模式
#define LCD_GRAPH_ON			      0x36		//打开绘图模式
#define LCD_GRAPH_OFF			      0x34		//关闭绘图模式
#ifndef LCD_COLOR
#define LCD_COLOR_BLACK			    1
#define LCD_COLOR_WHITE	

void  LCD12864_SetPoint(uchar X,uchar Y);    
void  LCD12864_CheckBusy(void);
void  LCD_WriteData(uchar Data);
void  LCD_WriteCmd(uchar CmdCode);
void  LCD12864_WriteString(uchar x,uchar y,uchar *Str);
void  LCD12864_Init(void);

//void LCD12864_WriteString(uchar x,uchar y,uchar *str); //指定位置显示一个字符串
//void LCD12864_WriteOneStr(uchar x,uchar y,uchar str);  //指定位置显示一个字符

#endif








