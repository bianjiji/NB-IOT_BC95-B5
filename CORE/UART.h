#ifndef _UART_H_   
#define _UART_H_   

#include <STC12C5A60S2.H>  
#include "delay.h"

//���������ʷ�������ֵ,1Tģʽ   
//Fosc = ����Ƶ��, Baud0 = ��׼������   
//RELOAD = 256 - INT(Fosc/Baud0/32 + 0.5)          
//Baud = Fosc/(256 - RELOAD)/32   
//error = (Baud - Baud0)/Baud0 * 100%  
   
//���崮��1�ڿ��أ��ر����ܽ�������   
#define OpenUART1()     ES=1   
#define CloseUART1()    ES=0   
#define OpenUART2()     IE2|=0x01   
#define CloseUART2()    IE2&=0xFE   
   
//���洮��1�ʹ���2���յ����ַ�   
//extern bit UART1_Recv_flag;  
//extern bit UART2_Recv_flag;
   
//extern bit PM_flag;			     //PM���ݽ��ձ�־��
//extern uchar idata PM_ReData[9]; //������յ���PM����
   
//����������  
void UART1_Init(uchar RELOAD, bit doubleBaud, bit timeMod);   
     
void UART2_Init(uchar RELOAD, bit doubleBaud, bit timeMod);   
     
void UART1_SendOneChar(uchar val);   
void UART1_SendOneByte(uchar val) ; 
void UART2_SendOneChar(uchar val);   
void UART2_Senddat(uint str[],uchar len); 
void UART1_SendStr(uchar *str);   
void UART1_Send_data(uchar str[],uchar len); 
void UART2_SendStr(uchar *str); 
void UART2_Send_data(uchar str[],uchar len);
void UART1_SendValue(uchar *value ,uint light)  ;
void UART2_SendValue(uchar *value ,uint light)  ;
#endif   
