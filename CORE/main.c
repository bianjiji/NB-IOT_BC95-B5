#include "STC12C5A60S2.h"
#include "illumination.h"
#include "12864.h"
#include "delay.h"
#include "UART.h"
#include "RhAndTemp.h"
//#include "LMS.h"
#include <string.h>
#include <stdio.h>
/****************宏定义**************************/
#define uint unsigned int
#define uchar unsigned char
#define Buf2_Max 10  
#define S2RI 0x01  
/****************串口初始值*********************/
#define  RELOAD      0xDC        //Fosc = 11.0592MHz, Baud0 = 9600  BRT=256-(11.0592M/32/9600/12^n)   
#define  doubleBaud  0   		 //波特率是否加倍，0不倍，1加倍 
#define  timeMod     1           //独立波特率发生器,0为12T模式，1为1T模式
/************************变量定义****************/
uchar code theme_one[]   = "xxxxxxxxxxxxxxxx";
uchar code theme_two[]   = "  xxxxxxxxxxxx  ";
uchar code theme_three[] = "  xxxxxxxxxxxx  ";
uchar code theme_four[]  = "    xxxxxx      "; 

uchar code dis_system[]  = "*****NB-IOT*****";
uchar code dis_illum[]   = "光照：      Lux "; 
uchar code dis_temp[]    = "温度：      ℃  "; 
uchar code dis_humidty[] = "湿度：      %   "; 
uint  Light_buf = 0;          //缓存光照数据
uint count=0,count1=0;Second_Int=0;            //计数
uchar UART_2Int_falg,temp2;//串口2中断标志及缓存变量
uchar LightBuff_Send_flag=0,LightBuff_Send_To_phone=0,num=0;
uchar sendDataBuf[30]={0};	  //把要发送的数据转换成十六进制数存入待发送的数组中
uchar RxCounter,RxBuffer[10];     //接收缓冲,最大USART_REC_LEN个字节.
uchar *strx;
extern uint temp_buf ;
extern uint Hum_buf;
uint Temperature, Humidty;
/************************函数声明****************/
void dis_init_screen(void);
void dis_data_screen(void);
void IntConfiguration(void);
void SerialInti(void);
void BC95Init(void);
void Timer0_Init(void);
void DATAToHEX(uint light);
//void DATAToHEX(uint pm,uint temp,uint humid,uint light);
/*****************************************************************************
*函数名       ：main
*函数功能     ：
*输入         ：
*输出         ：无
******************************************************************************/
void main(void)
{
	Init_guangzhao();                    //光照初始化
	LCD12864_Init();                  //LCD12864液晶屏初始化
	BC95Init();                      //NB_BC95-B5模块初始化
	delay_nMs(10);
	dis_init_screen();               //初始化显示菜单
	delay_1s(1);
	dis_data_screen();               //显示数据菜单
	Timer0_Init();                   //定时器0初始化
	SerialInti();                    //串口初始化
	UART1_Init( RELOAD,  doubleBaud,  timeMod);//UART1配置
	UART2_Init( RELOAD,  doubleBaud,  timeMod);//UART2配置
	while(1)
	   {
		   
		   Light_buf = Get_guangzhao();                    //采集光照
		   memset(sendDataBuf,0,sizeof(sendDataBuf));	    //清空数组sendDataBuf[];
		   //printf("光照强度:%dLux\r\n",Light_buf);
		   RHAndTemp();//采集温湿度
		   Temperature=temp_buf;
		   Humidty=Hum_buf;
		   Dispaly_tempAndHumidty(Temperature ,Humidty );//显示温湿度
		   if(LightBuff_Send_To_phone==1)//到达1s，上传数据
		   {
			   LightBuff_Send_To_phone=0;
			   DATAToHEX(Light_buf);
			   //通过串口1 发送数据
		       UART1_Send_data(sendDataBuf,5);
		   
		   }
            
		   
		   else if(LightBuff_Send_flag==1)//到达1分钟，上传数据
		   {
			   
			   LightBuff_Send_flag=0;
			   sprintf(&sendDataBuf[0], "AT+NMGS=5,00%08x\r\n",Light_buf);//将采集到的光照数据转换成十六进制上便于平台解析				
			   printf("%s\r\n",sendDataBuf);                              //验证数据是否正确，可以注释掉不用。
			   UART2_Send_data(sendDataBuf,30) ;                          //利用单片机串口2向NB模组发送数据上报到云平台
			   TR0 = 1; 
			   EA = 1;
			}

//		   DATAToHEX(0,temp_buf,Humidty_buf,Light_buf);
			 

		   
		}
	  
}
/*****************************************************************************
*函数名       ：void DATAToHEX(uint light)
*函数功能     :
			前2位作为帧头    最后一位作为帧尾   中间为数据 
			2个位的数据存入一个unsigned int的数据  
			缓存数组的低位存入一个传感器数据的高八位，
			缓存数组的高位存入一个传感器数据的低八位
******************************************************************************/

void DATAToHEX(uint light)
{

    sendDataBuf[0] =  0x88; 	  //帧头
	sendDataBuf[1] =  0x66;
	sendDataBuf[2] =  light/256;
	sendDataBuf[3] =  light%256;
	sendDataBuf[4] = 0xaa;               //帧尾                                     
}

void SerialInti(void)//初始化程序（必须使用，否则无法收发）
{

	TH1=0xfd;  //装入初值，波特率9600
	TL1=0xfd;
	TR1=1;   //打开定时器
	SM0=0;   //设置串行通讯工作模式，（10为一部发送，波特率可变，由定时器1的溢出率控制）
	SM1=1;   //(同上)在此模式下，定时器溢出一次就发送一个位的数据
	REN=1;   //串行接收允许位（要先设置sm0sm1再开串行允许）  
    TI=0;
	RI=0; 	
	EA=1; //	//开总中断	
	ES=1;      //串行口中断开  

}
/*****************************************************************************
*函数名       ：dis_init_screen
*函数功能     ：初始化菜单
*输入         ：
*输出         ：无
******************************************************************************/
void dis_init_screen(void)
{
	LCD12864_WriteString(1,0,theme_one);
	LCD12864_WriteString(2,0,theme_two);
	LCD12864_WriteString(3,0,theme_three);
	LCD12864_WriteString(4,0,theme_four);
}
/*****************************************************************************
*函数名       ：dis_data_screen
*函数功能     ：初始化菜单数据
*输入         ：
*输出         ：无
******************************************************************************/
void dis_data_screen(void)
{
	LCD12864_WriteString(1,0,dis_system);
	LCD12864_WriteString(2,0,dis_illum);
	LCD12864_WriteString(3,0,dis_temp);
	LCD12864_WriteString(4,0,dis_humidty);
}

/*****************************************************************************
*函数名       ：BC95Init
*函数功能     ：初始化NB—BC95模组
*输入         ：
*输出         ：无
******************************************************************************/
void BC95Init(void)
{
	//delay_nMs(500);//等待BC95初始化
	delay_nMs(100);
	UART2_SendStr("AT+NCDP=139.159.140.34,5683\r\n");//设置CDP（电信云的IP地址）
    delay_nMs(100);	
	UART2_SendStr("AT+NRB\r\n");                     //软件复位NB模块
    delay_nMs(100);	                                   
	UART2_SendStr("AT+NNMI=1\r\n");                  //通过NB模块自动收指令
	delay_nMs(100);
	UART2_SendStr("AT+CGATT=1\r\n");                 //设置NB模块的网络连接
	delay_nMs(100);	
}
///*****************************************************************************
//*函数名       ： void CLR_Buf2(void)
//*函数功能     ：清除缓存数据函数（串口2）
//*输入         ：
//*输出         ：无
//******************************************************************************/
//void CLR_Buf2(void)
//{
//    uint k;
//    for(k=0;k<Buf2_Max;k++)     
//    {
//        RxBuffer[k] = 0;
//    }
//    Second_Int = 0;              
//}
/*****************************************************************************
*函数名       ：Timer0_Init
*函数功能     ：定时器0初始化
*输入         ：
*输出         ：无
******************************************************************************/
void Timer0_Init(void)
{

    AUXR = 0x80;                    //timer0 work in 1T mode==1T模式
    TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
	TL0 = 0xCD;		
	TH0 = 0xD4;		//1ms
	TF0 = 0;
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
	EA  = 1;
	//count = 0;
}
/*****************************************************************************
*函数名       ：tm0_isr() interrupt 1 using 1
*函数功能     ：定时器中断服务子函数
*输入         ：
*输出         ：无
******************************************************************************/
void timer0_isr() interrupt 1 
{
	TL0 = 0xCD;		
	TH0 = 0xD4;		//1ms
	count++;
    if (count>1000)               //10ms * 100 -> 1s
    {
		count1++;
		count=0; 
		LightBuff_Send_To_phone = 1;
		if(count1>60)
        {	count1 = 0;               //reset counter
			LightBuff_Send_flag = 1;   
			EA=0;
			TR0=0;
		}
	}
}
/*****************************************************************************
*函数名       ：UART_2Interrupt(void) interrupt 8
*函数功能     ：串口2中断服务子函数
*输入         ：
*输出         ：无
******************************************************************************/
void UART_2Interrupt(void) interrupt 8
{
	IE2 = 0x00;                       //关闭串口2中断  
	if(S2CON&S2RI)
		{
			S2CON&=~S2RI;
			UART_2Int_falg=1;
			RxBuffer[Second_Int++]=S2BUF;
			if(Second_Int>Buf2_Max) 
				{ Second_Int=0;}
		} 
	IE2 = 0x01;                        //恢复串口2中断
}
#endif
