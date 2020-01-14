#include "12864.h"
void Delay_40US(void)   
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=17*12;a>0;a--);
}
/*************
测试LCD是否处于忙
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
向LCD写入字节数据
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
向LCD中写入指令代码
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
 12864设定初始显示位置
 X为行的数目
 Y为列的数目
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
	LCD_WriteCmd(0x30);       //选择基本指令集
	LCD_WriteCmd(0x0c);       //开显示(无游标、不反白)
	LCD_WriteCmd(0x01);       //清除显示，并且设定地址指针为00H
	LCD_WriteCmd(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位
}

void LCD12864_WriteString(uchar x,uchar y,uchar *Str)
{	  
//	if((y>4)||(x>8)) return;
	LCD12864_SetPoint(x,y);	
	while(*Str != '\0')	 //或是while(*str>0)   
	  { 
	       LCD_WriteData(*Str);
		   Str++;
      }
}
#endif


