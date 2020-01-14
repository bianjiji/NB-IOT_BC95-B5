#include "12864.h"
void Delay_40US(void)   
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=17*12;a>0;a--);
}
/*************
����LCD�Ƿ���æ
**************/
void LCD12864_CheckBusy(void)
{
    uchar Busy,num;
	  LcdData=0xff;
	  num=100;
    LCD12864_RS_L;
    LCD12864_RW_H;
    LCD12864_EN_H;
    Delay_40US();  
    Busy=LcdData&0x80;
    LCD12864_EN_L;
    while(Busy&num--);
}

/*********************************
��LCDд���ֽ�����
**********************************/
void LCD_WriteData(uchar Data)
{  
	LCD12864_CheckBusy();
	LCD12864_RS_H;
	LCD12864_RW_L;
	LCD12864_EN_L;
	LcdData=Data;
    Delay_40US();   
	LCD12864_EN_H;
    Delay_40US();    
	LCD12864_EN_L;
}
/*************************************
��LCD��д��ָ�����
**************************************/
void LCD_WriteCmd(uchar CmdCode)
{  
    LCD12864_CheckBusy();
   	LCD12864_RS_L;
   	LCD12864_RW_L;
   	LCD12864_EN_L;
    Delay_40US();   
   	LcdData=CmdCode;
    Delay_40US();   
   	LCD12864_EN_H;
    Delay_40US();   
   	LCD12864_EN_L;
}
/***********************
 12864�趨��ʼ��ʾλ��
 XΪ�е���Ŀ
 YΪ�е���Ŀ
 ***********************/
 void LCD12864_SetPoint(uchar X,uchar Y)
 {
 	uchar pos;
	//LCD_WriteCmd(0x30);
	if     (X==1){X=0x80;}
	else if(X==2){X=0x90;}
    else if(X==3){X=0x88;}
	else if(X==4){X=0x98;}
	pos=X+Y;
	LCD_WriteCmd(pos);
 }

void LCD12864_Init(void)
{   
	LCD_WriteCmd(0x34);
	LCD_WriteCmd(0x34);
	LCD_WriteCmd(0x30);       //ѡ�����ָ�
	LCD_WriteCmd(0x0c);       //����ʾ(���αꡢ������)
	LCD_WriteCmd(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
	LCD_WriteCmd(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ
}

void LCD12864_WriteString(uchar x,uchar y,uchar *Str)
{	  
//	if((y>4)||(x>8)) return;
	LCD12864_SetPoint(x,y);	
	while(*Str != '\0')	 //����while(*str>0)   
	  { 
	       LCD_WriteData(*Str);
		   Str++;
      }
}
#endif


