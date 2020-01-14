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

sbit LCD12864_RS=P2^5;    //���е�ָ��/����ѡ���ź�, H����, L����
sbit LCD12864_RW=P2^6;    //���ж�дѡ���ź�, H��, Lд
sbit LCD12864_EN=P2^7;    //����ʹ�ܶ�, H��Ч, L��Ч

#define LcdData P0

#define LCD12864_RS_L LCD12864_RS=0
#define LCD12864_RS_H LCD12864_RS=1
#define LCD12864_RW_L LCD12864_RW=0
#define LCD12864_RW_H LCD12864_RW=1
#define LCD12864_EN_L LCD12864_EN=0
#define LCD12864_EN_H LCD12864_EN=1

//����ָ�Ԥ����
#define	LCD_CLEAR_SCREEN       	0x01 	 	//����	
#define	LCD_ADDRESS_RESET      	0x02		//��ַ����	 
#define	LCD_BASIC_FUNCTION	  	0x30		//����ָ�
#define	LCD_EXTEND_FUNCTION	   	0x34		//����ָ�
//��չָ�Ԥ����
#define	LCD_AWAIT_MODE			    0x01	 	//����ģʽ	
#define LCD_ROLLADDRESS_ON		  0x03		//�������봹ֱ����ַ
#define LCD_IRAMADDRESS_ON	   	0x02		//��������IRAM��ַ	
#define	LCD_SLEEP_MODE			    0x08	 	//����˯��ģʽ
#define	LCD_NO_SLEEP_MODE	    	0x0c	 	//����˯��ģʽ
#define LCD_GRAPH_ON			      0x36		//�򿪻�ͼģʽ
#define LCD_GRAPH_OFF			      0x34		//�رջ�ͼģʽ
#ifndef LCD_COLOR
#define LCD_COLOR_BLACK			    1
#define LCD_COLOR_WHITE	

void  LCD12864_SetPoint(uchar X,uchar Y);    
void  LCD12864_CheckBusy(void);
void  LCD_WriteData(uchar Data);
void  LCD_WriteCmd(uchar CmdCode);
void  LCD12864_WriteString(uchar x,uchar y,uchar *Str);
void  LCD12864_Init(void);

//void LCD12864_WriteString(uchar x,uchar y,uchar *str); //ָ��λ����ʾһ���ַ���
//void LCD12864_WriteOneStr(uchar x,uchar y,uchar str);  //ָ��λ����ʾһ���ַ�

#endif








