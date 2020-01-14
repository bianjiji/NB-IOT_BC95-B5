#include "RhAndTemp.h"
#include "12864.h"
#include "delay.h"
////引脚定义
sbit  Port = P2^0;
//定义全局变量
uint temp_buf ;
uint Hum_buf;
//温湿度采集标志位
uchar  FLAG;
uchar  U8count,temp;
uchar  TX_data_H,TX_data_L,RH_TX_data_H,RH_TX_data_L,checkdata;
uchar  TX_data_H_temp,TX_data_L_temp,RH_TX_data_H_temp,RH_TX_data_L_temp,checkdata_temp;
uchar  recivedatadata;
/*************************************************************************************************
*函数名     ：dispaly_tempAndHumidty
*函数功能   ：在LCD显示温湿度
*输出       ：uint humidity,uint temp
*输入       ：无
*************************************************************************************************/
void Dispaly_tempAndHumidty(uint humidity,uint temp)
{
     //显示湿度
      LCD_WriteCmd(0x8b);
	 LCD_WriteData(humidity/100+0x30);
	 LCD_WriteData(humidity%100/10+0x30);
	 LCD_WriteData('.');
	 LCD_WriteData(humidity%10+0x30);

	 //显示温度
	
	 LCD_WriteCmd(0x9b);
	 LCD_WriteData(temp/100+0x30);
	 LCD_WriteData(temp%100/10+0x30);
	 LCD_WriteData('.');
	 LCD_WriteData(temp%10+0x30);   
} 
void  recivedata(void)
      {
	   uchar i;       
       for(i=0;i<8;i++)	   
	    {		
	   	    FLAG=2;	
	   	while((!Port)&&FLAG++);
		 Delay10us();Delay10us();Delay10us();Delay10us(); Delay10us();
	  		temp=0;
	     if(Port)temp=1;
		    FLAG=2;
		 while((Port)&&FLAG++);
	   	//超时则跳出for循环		  
	   	 if(FLAG==1)break;
	   	//判断数据位是0还是1	 	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 	   	 
		   recivedatadata<<=1;
	   	   recivedatadata|=temp;                    //0
	     }
	   
	}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== TX_data_H------
	//----温度低8位== TX_data_L------
	//----湿度高8位== RH_TX_data_H-----
	//----湿度低8位== RH_TX_data_L-----
	//----校验 8位 == checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,recivedata(); 
	//--------------------------------

void RHAndTemp(void)
	{
	  //主机拉低18ms 
       Port=0;
	   Delay25ms();
	   Port=1;
	 //总线由上拉电阻拉高 主机延时20us	
	   Delay50us();
	 //主机设为输入 判断从机响应信号 
	   Port=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	   if(!Port)		 //T !	  
	   {
	   FLAG=2;
	 //判断从机是否发出 80us 的低电平响应信号是否结束	 
	   while((!Port)&&FLAG++);
	   FLAG=2;
	 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
	   while((Port)&&FLAG++);
	 //数据接收状态		 
	   recivedata();
	   RH_TX_data_H_temp=recivedatadata;
	   recivedata();
	   RH_TX_data_L_temp=recivedatadata;
	   recivedata();
	   TX_data_H_temp=recivedatadata;
	   recivedata();
	   TX_data_L_temp=recivedatadata;
	   recivedata();
	   checkdata_temp=recivedatadata;
	   Port=1;
	   //数据校验 
	 
	   temp=(TX_data_H_temp+TX_data_L_temp+RH_TX_data_H_temp+RH_TX_data_L_temp);
	   if(temp==checkdata_temp)
		   {
		   	  RH_TX_data_H=RH_TX_data_H_temp;
		   	  RH_TX_data_L=RH_TX_data_L_temp;
			  TX_data_H=TX_data_H_temp;
		   	  TX_data_L=TX_data_L_temp;
		   	  checkdata=checkdata_temp;

			  Hum_buf =   (RH_TX_data_H<<8) + RH_TX_data_L;
			  temp_buf    =   (TX_data_H<<8)  + TX_data_L;
		   }
		 
      }	
	   delay_1s(1);	   
}




#endif




