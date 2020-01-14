#include "illumination.h"
#include "12864.h"
#include "UART.H"  
extern uint guangzhao=0;
void Init_guangzhao(void)
{
   //初始化BH1750，根据需要请参考pdf进行修改****
   Write_guangzhao(0x01);  
}

void  Write_guangzhao(uchar Address)               //单个写入数据
{
    guangzhao_Start();                  //起始信号
    BH1750_SendByte(SlaveAdd);   //发送设备地址+写信号
    BH1750_SendByte(Address);    //内部寄存器地址，请参考中文pdf22页 
  //BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    guangzhao_Stop();    
}
/*********************************************************
*函数名         :  read_BH1750_data
*函数功能       ：连续读出BH1750内部数据
*输入           :
*输出           ：
*********************************************************/
void read_BH1750_data(uchar Data[])
{   uchar i;	
    guangzhao_Start();                          //起始信号
    BH1750_SendByte(SlaveAdd+1);         //发送设备地址+读信号
	
	 for (i=0; i<3; i++)                     //连续读取6个地址数据，存储中Data
    {
        Data[i] = RecvByte();          //Data[0]存储0x32地址中的数据
        if (i == 3)
        {

           guangzhao_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {		
           guangzhao_SendACK(0);                 //回应ACK
        }
     }
     guangzhao_Stop();                           //停止信号
     delay_nMs(5);
}
/****************************************************************************
*函数名      ：guangzhao_Start
*函数功能    ：起始信号
*输入        ：无
*输出        ：无
*****************************************************************************/
void guangzhao_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay_5us(1);                //延时
    SDA = 0;                    //产生下降沿
    delay_5us(1);                //延时
    SCL = 0;                    //拉低时钟线
}
/*****************************************************************************
*函数名      ：guangzhao_Stop
*函数功能    ：停止信号
*输入        ：无
*输出        ：无
*****************************************************************************/
void guangzhao_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    delay_5us(1);                //延时
    SDA = 1;                    //产生上升沿
    delay_5us(1);                //延时
}

/*****************************************************************************
*函数名       ：guangzhao_SendACK
*函数功能     ：发送应答信号
*输入         ：入口参数:ack (0:ACK 1:NAK)
*输出         ：无
******************************************************************************/
void guangzhao_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay_5us(1);                //延时
    SCL = 0;                    //拉低时钟线
    delay_5us(1);                 //延时
}
/****************************************************************************
*函数名：	  ：BH1750_RecvACK
*函数功能     ：接收应答信号
*输入         ：无
*输出         ：bit
*****************************************************************************/
bit BH1750_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    delay_5us(1);                //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    delay_5us(1);                  //延时

    return CY;
}
/*****************************************************************************
*函数名        ：BH1750_SendByte
*函数功能      ：向IIC总线发送一个字节数据
*输入          ：BYTE dat
*输出          ：无
******************************************************************************/
void BH1750_SendByte(BYTE dat)
{
    BYTE i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        delay_5us(1);            //延时
        SCL = 0;                //拉低时钟线
        delay_5us(1);            //延时
    }
    BH1750_RecvACK();
}
/*******************************************************************************
*函数名         ：RecvByte
*函数功能       ：从IIC总线接收一个字节数据
*输入           ：无
*输出			：BYTE
********************************************************************************/
BYTE RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        delay_5us(1);            //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        delay_5us(1);            //延时
    }
    return dat;
}
/********************************************************************************
*函数名        ：Get_guangzhao
*函数功能      ：获取光照数据
*输入          ：无
*输出          ：uint
*********************************************************************************/
uint Get_guangzhao(void)
{
  uchar guangzhao_buf[8];
  Write_guangzhao(0x01);      // power on
  Write_guangzhao(0x10);      // H- resolution mode
	delay_nMs(180); 
	read_BH1750_data(guangzhao_buf); //采集传感器的数据
	guangzhao = guangzhao_buf[0];
	guangzhao = (guangzhao<<8) + guangzhao_buf[1];
	guangzhao = (uint)(guangzhao/1.2);

    LCD_WriteCmd(0X93);
    LCD_WriteData(guangzhao/10000+0x30);
    LCD_WriteData(guangzhao%10000/1000+0x30);
    LCD_WriteData(guangzhao%10000%1000/100+0x30);
    LCD_WriteData(guangzhao%10000%1000%100/10+0x30);
    LCD_WriteData(guangzhao%10+0x30);
    return guangzhao;
}

#endif