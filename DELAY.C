#include "PROJECT.H"

/* MILLISECOND DELAY */

void delay_milliseconds(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 12000; j++);
    }
}

/* SECOND DELAY */

void delay_seconds(unsigned int seconds)
{
    unsigned int i;

    for(i = 0; i < seconds; i++)
    {
        delay_milliseconds(1000);
    }
}