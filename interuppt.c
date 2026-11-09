#include<LPC21xx.h>
#define EINTO 1<<0
void EINT0_INIT(void);


void EINT0_INIT(void)
{	
	PINSEL1=EINTO;
	VICIntSelect=0x00000000;
	VICVectCntl0=(0x20)|14;
	VICVectAddr0= (int)EXT_INTO_isr;
	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=1<<14;
}
