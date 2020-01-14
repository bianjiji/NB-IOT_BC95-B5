#ifndef _UART_H_   
#define _UART_H_   

#include <STC12C5A60S2.H>  
#include "delay.h"

//独立波特率发生器初值,1T模式   
//Fosc = 晶振频率, Baud0 = 标准波特率   
//RELOAD = 256 - INT(Fosc/Baud0/32 + 0.5)          
//Baud = Fosc/(256 - RELOAD)/32   
//error = (Baud - Baud0)/Baud0 * 100%  
   
//定义串口1口开关，关闭则不能接收数据   
#define OpenUART1()     ES=1   
#define CloseUART1()    ES=0   
#define OpenUART2()     IE2|=0x01   
#define CloseUART2()    IE2&=0xFE   
   
//缓存串口1和串口2接收到的字符   
//extern bit UART1_Recv_flag;  
//extern bit UART2_Recv_flag;
   
//extern bit PM_flag;			     //PM数据接收标志符
//extern uchar idata PM_ReData[9]; //缓存接收到的PM数据
   
//函数的声明  
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
