#include "PROJECT.H"
#include <string.h>

#define GREEN_LED (1<<23)
#define RED_LED   (1<<24)
#define BUZZER    (1<<25)
#define BUTTON    (1<<26)

/* ALERT INITIALIZATION */

void ALERT_INIT(void)
{
    IODIR1 |= GREEN_LED | RED_LED | BUZZER;
    IODIR1 &= ~BUTTON;

    IOSET1 = GREEN_LED | RED_LED | BUZZER;
}

/* NORMAL MESSAGE */

void NORMAL_ALERT(void)
{
    IOSET1 = RED_LED | BUZZER;
    IOCLR1 = GREEN_LED;
}

/* EMERGENCY MESSAGE */

void EMERGENCY_ALERT(void)
{
    IOSET1 = GREEN_LED;
    IOCLR1 = RED_LED | BUZZER;

    GSM_TRANSMIT("EMERGENCY ALERT! Please check immediate");
}

/* BUZZER OFF */

void BUZZER_OFF(void)
{
    IOSET1 = BUZZER;
}

/* PUSH BUTTON CHECK */

void BUTTON_CHECK(void)
{
    if((IOPIN1 & BUTTON) == 0)
    {
        BUZZER_OFF();
    }
}

/* GSM INITIALIZATION */

void GSM_INIT(void)
{
    UART0_STRING("AT\r\n");
    delay_milliseconds(1000);

    UART0_STRING("AT\r\n");
    delay_milliseconds(1000);

    UART0_STRING("AT+CMGF=1\r\n");
    delay_milliseconds(1000);

    UART0_STRING("AT+CNMI=2,2,0,0,0\r\n");
    delay_milliseconds(1000);
}

/* GSM TRANSMISSION */

void GSM_TRANSMIT(char *s)
{
    UART0_STRING("AT+CMGF=1\r\n");
    delay_milliseconds(1000);

    UART0_STRING("AT+CMGS=\"+91XXXXXXXXXX\"\r\n");
    delay_milliseconds(1000);

    UART0_STRING(s);
    delay_milliseconds(1000);

    UART0_TX(26);

    delay_seconds(5);
}

/* GSM RECEPTION */

void GSM_RECEIVE(void)
{
    unsigned char ch;
    unsigned int i = 0;
    unsigned char capture = 0;
    char msg[160];

    while(1)
    {
        BUTTON_CHECK();

        if(U0LSR & 0x01)
        {
            ch = U0RBR;

            /* START DATA CAPTURE */

            if(ch == '*')
            {
                i = 0;
                capture = 1;
                continue;
            }

            /* STOP DATA CAPTURE */

            if(ch == '#' && capture == 1)
            {
                msg[i] = '\0';
                capture = 0;

                LCD_COMMAND(0x01);
                LCD_COMMAND(0x80);
                LCD_STR(msg);

                /* CHECK EMERGENCY MESSAGE */

                if(strstr(msg,"EMERGENCY") != NULL)
                {
                    EMERGENCY_ALERT();
                }
                else
                {
                    NORMAL_ALERT();
                }

                i = 0;
            }

            /* STORE DATA BETWEEN * AND # */

            else if(capture == 1)
            {
                if(i < 159)
                {
                    msg[i++] = ch;
                }
            }
        }
    }
}