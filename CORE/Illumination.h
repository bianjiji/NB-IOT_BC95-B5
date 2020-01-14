#ifndef _ILLUMINATION_H
#define _ILLUMINATION_H

#include"stc12c5a60s2.h"
#include"delay.h"
//�궨��
#define	  SlaveAdd   0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��ַΪ0x3A

typedef unsigned char BYTE;
typedef unsigned int  WORD; 
//���Ŷ���
sbit	  SCL = P2^2;      //IICʱ�����Ŷ���
sbit  	  SDA = P2^1;      //IIC�������Ŷ���

//����������
extern void  Init_guangzhao(void);
extern void  Write_guangzhao(uchar Address);                //����д������
//extern uchar Single_Read_BH1750(uchar Address);                 //������ȡ�ڲ��Ĵ�������
extern void  read_BH1750_data(uchar Data[]);                     //�����Ķ�ȡ�ڲ��Ĵ�������
extern void  guangzhao_Start();                                        //��ʼ�ź�
extern void  guangzhao_Stop();                                         //ֹͣ�ź�
extern void  guangzhao_SendACK(bit ack);                               //Ӧ��ACK
extern bit   BH1750_RecvACK();                                      //��ack
extern void  BH1750_SendByte(BYTE dat);                             //IIC�����ֽ�д
extern BYTE  RecvByte();                                     //IIC�����ֽڶ�
extern uint Get_guangzhao(void);									 //��ȡ���յ�����

#endif
