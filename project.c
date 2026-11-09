#include <LPC21xx.h>
#include<string.h>
#include "lcd.c"
#include "uart0.c"
#define EINTO 1<<0;
#define LED1 1<<5
#define LED2 1<<6
#define BUZZ 1<<7
	unsigned char str[100];
	unsigned char flag=1;
	void EXT_INTO_isr(void)__irq
{
	EXTINT=0x01;
	flag= !flag;
	VICVectAddr=0;

}


int main()
{
		unsigned char s;
		unsigned int i=0;
		unsigned int j=0;
	
	PINSEL1=EINTO;
	VICIntSelect=0x00000000;
	VICVectCntl0=(0x20)|14;
	VICVectAddr0= (int)EXT_INTO_isr;
	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=1<<14;		 
while(1)
 {
	if(flag)
	
	{

		LCD_INIT();
		LCD_COMMAND(0x80);
		LCD_STRING("WEATHER REPORT");
		UART0_STR("at\r/n");
		UART0_STR("at+cmgf=1\r\n");
		UART0_STR("at+cnmi=2,2,2,0,0\r\n");
		while(1)
		{
				   s=UART0_RX();
		if(s=='\r' || s=='\n')
				   break;
		else
				   str[i++]=s ;	  
		}
					str[i]='\0';

	if(strstr((const char *)s,"URGENT"))
	 {
	 			UART0_STR(str);
	 			IOSET0=LED1|LED2|BUZZ;
				IOCLR0=BUZZ;
				while(j<=25)
				{
					IOCLR0=LED1;
					delay_milliseconds(500);
					IOSET0=LED2;
					delay_milliseconds(500);
					j++;
				}
				
				LCD_STRING(str);
	}
		
	else
		{
			IOSET0=LED1|LED2|BUZZ;
			IOCLR0=LED2;
			LCD_COMMAND(0x80);
			LCD_STRING(str);
		}
		}
		else
		{	
		LCD_COMMAND(0x01);
		IOSET0=LED1|LED2|BUZZ;
		i=0;
		
		}
		}
		}


	

