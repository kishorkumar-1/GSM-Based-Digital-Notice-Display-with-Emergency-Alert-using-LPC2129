
 #define LCD_d 0xff<<10
#define RS 1<<8
#define E 1<<9
#include "delay.c"
void LCD_INIT(void);
void LCD_COMMAND(unsigned char cmd);
void LCD_DATA(unsigned char d);
void LCD_STRING(unsigned char *s);

void LCD_INIT(void)
{
	IODIR0=LCD_d|RS|E;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x02);
	LCD_COMMAND(0x0C);
	LCD_COMMAND(0x28);
}

void LCD_COMMAND(unsigned char cmd)
{
	IOCLR0 = LCD_d;
	IOSET0=(cmd&0XF0)<<10;
	IOCLR0=RS;
	IOSET0=E;
	delay_milliseconds(2);
	IOCLR0=E;

	IOCLR0 = LCD_d;
	IOSET0=(cmd&0X0F)<<14;
	IOCLR0=RS;
	IOSET0=E;
	delay_milliseconds(2);
	IOCLR0=E;
}

void LCD_DATA(unsigned char d)
{
	IOCLR0 = LCD_d;
	IOSET0=(d&0XF0)<<10;
	IOSET0=RS;
	IOSET0=E;
	delay_milliseconds(2);
	IOCLR0=E;

	IOCLR0 = LCD_d;
	IOSET0=(d&0X0F)<<14;
	IOSET0=RS;
	IOSET0=E;
	delay_milliseconds(2);
	IOCLR0=E;
}

void LCD_STRING(unsigned char *s)
{
    while(*s)
    {
        LCD_DATA(*s++);
        delay_milliseconds(300);
        LCD_COMMAND(0x18);  // Shift display left
    }
}

	
