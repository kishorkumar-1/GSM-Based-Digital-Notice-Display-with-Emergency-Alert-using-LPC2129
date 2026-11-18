#include "PROJECT.H"

int main(void)
{
    UART0_CONFIG();

    LCD_INIT();

    ALERT_INIT();

    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);
    LCD_STR("GSM PROJECT");

    GSM_INIT();

    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);
    LCD_STR("WAITING FOR SMS");

    GSM_RECEIVE();

    while(1);

    return 0;
}