#include"delay.h"
#include "intrins.h"
//void delay_1Ms(void)
//{
//   unsigned char a,b;
//     for(b=129;b>0;b--)
//       for(a=45;a>0;a--);
//}
void delay_nMs(uint num)
{
    unsigned char a,b,c;
	 for(c=num;c>0;c--)
       for(b=129;b>0;b--)
         for(a=45;a>0;a--);
}
//void delay_500us(void)
//{
//    unsigned char a,b,c;
//    for(c=1;c>0;c--)
//        for(b=222;b>0;b--)
//            for(a=12;a>0;a--);
//}
void delay_5us(uchar num)
{
    unsigned char a,b;
	for(;num>0;num--)
      for(b=3;b>0;b--)
        for(a=8;a>0;a--);
}

void delay_1s(int num) //ÑÓÊ±Ò»Ãë
{
   uchar a,b,c;
   while(num--)
    for(c=142;c>0;c--)
        for(b=168;b>0;b--)
            for(a=250;a>0;a--);
             // for(n=1;n>0;n--);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 1;
	j = 133;
	do
	{
		while (--j);
	} while (--i);
}

	
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}
void Delay25ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

