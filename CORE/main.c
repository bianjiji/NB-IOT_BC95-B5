#include "STC12C5A60S2.h"
#include "illumination.h"
#include "12864.h"
#include "delay.h"
#include "UART.h"
#include "RhAndTemp.h"
//#include "LMS.h"
#include <string.h>
#include <stdio.h>
/****************�궨��**************************/
#define uint unsigned int
#define uchar unsigned char
#define Buf2_Max 10  
#define S2RI 0x01  
/****************���ڳ�ʼֵ*********************/
#define  RELOAD      0xDC        //Fosc = 11.0592MHz, Baud0 = 9600  BRT=256-(11.0592M/32/9600/12^n)   
#define  doubleBaud  0   		 //�������Ƿ�ӱ���0������1�ӱ� 
#define  timeMod     1           //���������ʷ�����,0Ϊ12Tģʽ��1Ϊ1Tģʽ
/************************��������****************/
uchar code theme_one[]   = "xxxxxxxxxxxxxxxx";
uchar code theme_two[]   = "  xxxxxxxxxxxx  ";
uchar code theme_three[] = "  xxxxxxxxxxxx  ";
uchar code theme_four[]  = "    xxxxxx      "; 

uchar code dis_system[]  = "*****NB-IOT*****";
uchar code dis_illum[]   = "���գ�      Lux "; 
uchar code dis_temp[]    = "�¶ȣ�      ��  "; 
uchar code dis_humidty[] = "ʪ�ȣ�      %   "; 
uint  Light_buf = 0;          //�����������
uint count=0,count1=0;Second_Int=0;            //����
uchar UART_2Int_falg,temp2;//����2�жϱ�־���������
uchar LightBuff_Send_flag=0,LightBuff_Send_To_phone=0,num=0;
uchar sendDataBuf[30]={0};	  //��Ҫ���͵�����ת����ʮ����������������͵�������
uchar RxCounter,RxBuffer[10];     //���ջ���,���USART_REC_LEN���ֽ�.
uchar *strx;
extern uint temp_buf ;
extern uint Hum_buf;
uint Temperature, Humidty;
/************************��������****************/
void dis_init_screen(void);
void dis_data_screen(void);
void IntConfiguration(void);
void SerialInti(void);
void BC95Init(void);
void Timer0_Init(void);
void DATAToHEX(uint light);
//void DATAToHEX(uint pm,uint temp,uint humid,uint light);
/*****************************************************************************
*������       ��main
*��������     ��
*����         ��
*���         ����
******************************************************************************/
void main(void)
{
	Init_guangzhao();                    //���ճ�ʼ��
	LCD12864_Init();                  //LCD12864Һ������ʼ��
	BC95Init();                      //NB_BC95-B5ģ���ʼ��
	delay_nMs(10);
	dis_init_screen();               //��ʼ����ʾ�˵�
	delay_1s(1);
	dis_data_screen();               //��ʾ���ݲ˵�
	Timer0_Init();                   //��ʱ��0��ʼ��
	SerialInti();                    //���ڳ�ʼ��
	UART1_Init( RELOAD,  doubleBaud,  timeMod);//UART1����
	UART2_Init( RELOAD,  doubleBaud,  timeMod);//UART2����
	while(1)
	   {
		   
		   Light_buf = Get_guangzhao();                    //�ɼ�����
		   memset(sendDataBuf,0,sizeof(sendDataBuf));	    //�������sendDataBuf[];
		   //printf("����ǿ��:%dLux\r\n",Light_buf);
		   RHAndTemp();//�ɼ���ʪ��
		   Temperature=temp_buf;
		   Humidty=Hum_buf;
		   Dispaly_tempAndHumidty(Temperature ,Humidty );//��ʾ��ʪ��
		   if(LightBuff_Send_To_phone==1)//����1s���ϴ�����
		   {
			   LightBuff_Send_To_phone=0;
			   DATAToHEX(Light_buf);
			   //ͨ������1 ��������
		       UART1_Send_data(sendDataBuf,5);
		   
		   }
            
		   
		   else if(LightBuff_Send_flag==1)//����1���ӣ��ϴ�����
		   {
			   
			   LightBuff_Send_flag=0;
			   sprintf(&sendDataBuf[0], "AT+NMGS=5,00%08x\r\n",Light_buf);//���ɼ����Ĺ�������ת����ʮ�������ϱ���ƽ̨����				
			   printf("%s\r\n",sendDataBuf);                              //��֤�����Ƿ���ȷ������ע�͵����á�
			   UART2_Send_data(sendDataBuf,30) ;                          //���õ�Ƭ������2��NBģ�鷢�������ϱ�����ƽ̨
			   TR0 = 1; 
			   EA = 1;
			}

//		   DATAToHEX(0,temp_buf,Humidty_buf,Light_buf);
			 

		   
		}
	  
}
/*****************************************************************************
*������       ��void DATAToHEX(uint light)
*��������     :
			ǰ2λ��Ϊ֡ͷ    ���һλ��Ϊ֡β   �м�Ϊ���� 
			2��λ�����ݴ���һ��unsigned int������  
			��������ĵ�λ����һ�����������ݵĸ߰�λ��
			��������ĸ�λ����һ�����������ݵĵͰ�λ
******************************************************************************/

void DATAToHEX(uint light)
{

    sendDataBuf[0] =  0x88; 	  //֡ͷ
	sendDataBuf[1] =  0x66;
	sendDataBuf[2] =  light/256;
	sendDataBuf[3] =  light%256;
	sendDataBuf[4] = 0xaa;               //֡β                                     
}

void SerialInti(void)//��ʼ�����򣨱���ʹ�ã������޷��շ���
{

	TH1=0xfd;  //װ���ֵ��������9600
	TL1=0xfd;
	TR1=1;   //�򿪶�ʱ��
	SM0=0;   //���ô���ͨѶ����ģʽ����10Ϊһ�����ͣ������ʿɱ䣬�ɶ�ʱ��1������ʿ��ƣ�
	SM1=1;   //(ͬ��)�ڴ�ģʽ�£���ʱ�����һ�ξͷ���һ��λ������
	REN=1;   //���н�������λ��Ҫ������sm0sm1�ٿ���������  
    TI=0;
	RI=0; 	
	EA=1; //	//�����ж�	
	ES=1;      //���п��жϿ�  

}
/*****************************************************************************
*������       ��dis_init_screen
*��������     ����ʼ���˵�
*����         ��
*���         ����
******************************************************************************/
void dis_init_screen(void)
{
	LCD12864_WriteString(1,0,theme_one);
	LCD12864_WriteString(2,0,theme_two);
	LCD12864_WriteString(3,0,theme_three);
	LCD12864_WriteString(4,0,theme_four);
}
/*****************************************************************************
*������       ��dis_data_screen
*��������     ����ʼ���˵�����
*����         ��
*���         ����
******************************************************************************/
void dis_data_screen(void)
{
	LCD12864_WriteString(1,0,dis_system);
	LCD12864_WriteString(2,0,dis_illum);
	LCD12864_WriteString(3,0,dis_temp);
	LCD12864_WriteString(4,0,dis_humidty);
}

/*****************************************************************************
*������       ��BC95Init
*��������     ����ʼ��NB��BC95ģ��
*����         ��
*���         ����
******************************************************************************/
void BC95Init(void)
{
	//delay_nMs(500);//�ȴ�BC95��ʼ��
	delay_nMs(100);
	UART2_SendStr("AT+NCDP=139.159.140.34,5683\r\n");//����CDP�������Ƶ�IP��ַ��
    delay_nMs(100);	
	UART2_SendStr("AT+NRB\r\n");                     //�����λNBģ��
    delay_nMs(100);	                                   
	UART2_SendStr("AT+NNMI=1\r\n");                  //ͨ��NBģ���Զ���ָ��
	delay_nMs(100);
	UART2_SendStr("AT+CGATT=1\r\n");                 //����NBģ�����������
	delay_nMs(100);	
}
///*****************************************************************************
//*������       �� void CLR_Buf2(void)
//*��������     ������������ݺ���������2��
//*����         ��
//*���         ����
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
*������       ��Timer0_Init
*��������     ����ʱ��0��ʼ��
*����         ��
*���         ����
******************************************************************************/
void Timer0_Init(void)
{

    AUXR = 0x80;                    //timer0 work in 1T mode==1Tģʽ
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
*������       ��tm0_isr() interrupt 1 using 1
*��������     ����ʱ���жϷ����Ӻ���
*����         ��
*���         ����
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
*������       ��UART_2Interrupt(void) interrupt 8
*��������     ������2�жϷ����Ӻ���
*����         ��
*���         ����
******************************************************************************/
void UART_2Interrupt(void) interrupt 8
{
	IE2 = 0x00;                       //�رմ���2�ж�  
	if(S2CON&S2RI)
		{
			S2CON&=~S2RI;
			UART_2Int_falg=1;
			RxBuffer[Second_Int++]=S2BUF;
			if(Second_Int>Buf2_Max) 
				{ Second_Int=0;}
		} 
	IE2 = 0x01;                        //�ָ�����2�ж�
}
#endif
