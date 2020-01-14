#include <intrins.h>   
#include "UART.H"   
//���洮��1�ʹ���2��־�� 
//bit UART1_Recv_flag = 0;   
//bit UART2_Recv_flag = 0;
#define S2RI 0x01    
#define S2TI 0x02    
//bit PM_flag = 0;
//uchar idata PM_ReData[9];
uchar flag1,temp1; 
void UART1_Init(uchar RELOAD, bit doubleBaud, bit timeMod)   
{   
    SCON |= 0x50;                     //����1��ʽ1,���ճ���      
    BRT = RELOAD;                     //������9600   BRT=256-(11.0592M/32/9600/12^n) =0Xdc    
    if (timeMod == 1)                 //1T   
    {                                 //T0x12   T1x12   UM0x6   BRTR    S2SMOD  BRTx12  EXTRAM  S1BRS   
        AUXR |= 0x15;                 //����1ʹ�ö��������ʷ����������������ʷ�����1T   
    }   
    else                              //12T   
    {   
        AUXR |= 0x11;   
    }      
    if (doubleBaud == 1)   
    {   
        PCON |= 0x80;                 //�����ʼӱ�   
    }   
    else   
    {   
        PCON &= 0x7F;                  //�����ʲ��ӱ�   
    }   
    EA = 1;   
    ES = 1;                            //������1�ж�  
	
}    
void UART2_Init(uchar RELOAD, bit doubleBaud, bit timeMod)   
{   
                                       //S2SM0  S2SM1   S2SM2   S2REN   S2TB8   S2RB8   S2TI     S2RI   
    S2CON |= 0x50;                     //����2,��ʽ1�����ճ���      
    BRT = RELOAD;   
    if (timeMod == 1)                  //1T   
    {   
                                       //T0x12   T1x12   UM0x6   BRTR    S2SMOD  BRTx12  EXTRAM  S1BRS   
        AUXR |= 0x14;                  //����1ʹ�ö��������ʷ����������������ʷ�����1T   
    }   
    else                               //12T   
    {   
        AUXR = (AUXR | 0x10) & 0xFB;   
    }   
   
    if (doubleBaud == 1)   
    {   
        AUXR |= 0x08;                   //�����ʼӱ�   
    }   
    else   
    {   
        AUXR &= 0xF7;                   //�����ʲ��ӱ�   
    }   
   	AUXR1 &= 0xef;						//����2��P1��ͨ��
    EA = 1;                             //-   -   -    -    -    -     ESPI    ES2   
    IE2 |= 0x01;                        //������2�ж�              
}     
void UART1_SendOneChar(uchar val)   
{   
    //ES = 0;                           //�رմ���1�ж�   
   
    SBUF = val;   
    while(TI == 0);   
    TI = 0;   
   
    //ES = 1;                           //�ָ�����1�ж�   
}                             
void UART1_Send_data(uchar str[],uchar len)   
{   
    uchar i =0;
    for(;i<len;i++)   
    {   
        UART1_SendOneChar(str[i]);   
    }   
}      
//void UART1_SendStr(uchar *str)   
//{   
//    while( (*str)!='\0' )   
//    {   
//        UART1_SendOneChar(*str);   
//        str++;   
//    }   
//}  
void UART1_SendOneByte(uchar val)   //����1byte����
{   
    //ES = 0;                           //�رմ���1�ж�   
   
    SBUF = val;   
    while(TI == 0);   
    TI = 0;   
   
    //ES = 1;                           //�ָ�����1�ж�   
}  
void UART2_SendOneChar(uchar val)   
{   
    //IE2 = 0x00;                       //�رմ���2�ж�      
    S2BUF = val;       
    while ((S2CON & 0x02) == 0);   
    S2CON &= 0xFD;      
    //IE2 = 0x01;                        //�ָ�����2�ж�   
}        
void UART2_SendStr(uchar *str)   
{   
    while( (*str)!='\0' )   
    {   
        UART2_SendOneChar(*str);   
        str++;   
    }   
}   
void UART2_Send_data(uchar str[],uchar len)   
{   
    uchar i =0;
    for(;i<len;i++)   
    {   
        UART2_SendOneChar(str[i]);   
    }   
}  
//��дputchar����
uchar putchar(uchar c)
{
    UART1_SendOneByte(c);
    return c;
}
//void UART_2SendOneByte(uchar val)
//{
//    S2BUF = val;
//    while(!(S2CON&S2TI));  //��S2TI=0,�ڴ˵ȴ�
//    S2CON&=~S2TI;      //S2TI=0
//}
  
//void UART2_Senddat(uchar str[],uchar len)   
//{   
//    uchar i =0;
//    for(;i<len;i++)   
//    {   
//        UART_2SendOneByte(str[i]);
//        //UART1_SendOneByte(str[i]);   		
//    }   
//} 
//void UART2_Int(void) interrupt 8   
//{   

//    if ((S2CON & 0x01) == 1)   
//    {   
//        S2CON &= 0xFE;   
//        //PM_ReData[count] = S2BUF;
//  
//    }      
//}  
/************����1�ж�*************/
void UART_1Interrupt(void) interrupt 4
{
	if(RI==1)
		{
			RI=0;
			flag1=1;
			temp1=SBUF;
		}
}
