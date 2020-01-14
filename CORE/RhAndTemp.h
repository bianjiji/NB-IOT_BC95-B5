#ifndef _RHANDTEMP_H__
#define _RHANDTEMP_H__

#include "stc12c5a60s2.h"
//#include "headfile.h"
#ifndef uchar
#define  uchar unsigned char
#endif
#ifndef uint
#define  uint unsigned int
#endif

extern void Dispaly_tempAndHumidty(uint humidity,uint temp);
void recivedata(void);
extern void RHAndTemp(void);
#endif

													