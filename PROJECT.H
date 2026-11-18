#ifndef PROJECT_H
#define PROJECT_H

#include <LPC21XX.H>

/* LCD PIN CONFIGURATION */

#define LCD_d ((1<<18)|(1<<19)|(1<<21)|(1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<27))
#define RS    (1<<8)
#define E     (1<<9)

/* ALERT FUNCTIONS */

void ALERT_INIT(void);
void NORMAL_ALERT(void);
void EMERGENCY_ALERT(void);
void BUZZER_OFF(void);
void BUTTON_CHECK(void);

/* LCD FUNCTIONS */

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INTEGER(int);
void LCD_STR(char *);

/* DELAY FUNCTIONS */

void delay_seconds(unsigned int);
void delay_milliseconds(unsigned int);

/* UART FUNCTIONS */

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_STRING(char *);
unsigned char UART0_RX(void);

/* GSM FUNCTIONS */

void GSM_INIT(void);
void GSM_TRANSMIT(char *);
void GSM_RECEIVE(void);

#endif