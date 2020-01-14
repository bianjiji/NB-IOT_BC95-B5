#include "RhAndTemp.h"
#include "12864.h"
#include "delay.h"
////���Ŷ���
sbit  Port = P2^0;
//����ȫ�ֱ���
uint temp_buf ;
uint Hum_buf;
//��ʪ�Ȳɼ���־λ
uchar  FLAG;
uchar  U8count,temp;
uchar  TX_data_H,TX_data_L,RH_TX_data_H,RH_TX_data_L,checkdata;
uchar  TX_data_H_temp,TX_data_L_temp,RH_TX_data_H_temp,RH_TX_data_L_temp,checkdata_temp;
uchar  recivedatadata;
/*************************************************************************************************
*������     ��dispaly_tempAndHumidty
*��������   ����LCD��ʾ��ʪ��
*���       ��uint humidity,uint temp
*����       ����
*************************************************************************************************/
void Dispaly_tempAndHumidty(uint humidity,uint temp)
{
     //��ʾʪ��
      LCD_WriteCmd(0x8b);
	 LCD_WriteData(humidity/100+0x30);
	 LCD_WriteData(humidity%100/10+0x30);
	 LCD_WriteData('.');
	 LCD_WriteData(humidity%10+0x30);

	 //��ʾ�¶�
	
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
	   	//��ʱ������forѭ��		  
	   	 if(FLAG==1)break;
	   	//�ж�����λ��0����1	 	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 	   	 
		   recivedatadata<<=1;
	   	   recivedatadata|=temp;                    //0
	     }
	   
	}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== TX_data_H------
	//----�¶ȵ�8λ== TX_data_L------
	//----ʪ�ȸ�8λ== RH_TX_data_H-----
	//----ʪ�ȵ�8λ== RH_TX_data_L-----
	//----У�� 8λ == checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay_10us();,recivedata(); 
	//--------------------------------

void RHAndTemp(void)
	{
	  //��������18ms 
       Port=0;
	   Delay25ms();
	   Port=1;
	 //������������������ ������ʱ20us	
	   Delay50us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	   Port=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	   if(!Port)		 //T !	  
	   {
	   FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
	   while((!Port)&&FLAG++);
	   FLAG=2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	   while((Port)&&FLAG++);
	 //���ݽ���״̬		 
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
	   //����У�� 
	 
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




