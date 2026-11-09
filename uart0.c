
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char *s) ;

void UART0_CONFIG(void)
{
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x3;
	}
void UART0_TX(unsigned char ch)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=ch;
}
unsigned char UART0_RX(void)
{
	while((U0LSR & 0x1)==0);
	return U0RBR;

	}
void UART0_STR(unsigned char *s)
{
	while(*s);
	UART0_TX(*s++);
}


