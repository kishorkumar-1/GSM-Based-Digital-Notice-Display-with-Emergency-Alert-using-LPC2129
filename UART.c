#include <LPC21XX.H>
#include "PROJECT.H"

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_STRING(char *);
unsigned char UART0_RX(void);

/* UART CONFIGURATION */

void UART0_CONFIG(void)
{
    PINSEL0 = (PINSEL0 & ~0x0F) | 0x05;

    U0LCR = 0x83;
    U0DLL = 98;
    U0DLM = 0;
    U0LCR = 0x03;
}

/* UART TRANSMISSION */

void UART0_TX(unsigned char ch)
{
    while((U0LSR & (1<<5)) == 0);

    U0THR = ch;
}

/* UART STRING TRANSMISSION */

void UART0_STRING(char *str)
{
    while(*str)
    {
        UART0_TX(*str);
        str++;
    }
}

/* UART RECEPTION */

unsigned char UART0_RX(void)
{
    while((U0LSR & (1<<0)) == 0);

    return U0RBR;
}