#ifndef _DELAY_H
#define _DELAY_H
#include  "intrins.h"
//�궨��
#define uint  unsigned int
#define uchar unsigned char
 
//����������
void delay_1Ms(void);
void delay_nMs(uint num);
//void delay_500us(void);
void delay_5us(uchar num);
//void delay_10us(uchar num);													           
void Delay10us();		//@11.0592MHz
void delay_1s(int num);
void Delay50us();		//@11.0592MHz
void Delay25ms();		//@11.0592MHz
//void delay_nms(uint num);
//void dealy_40us(void);

#endif 