void delay_seconds(unsigned int seconds);
void delay_milliseconds(unsigned int ms);

void delay_seconds(unsigned int seconds)
{
	T0PR=15000000-1;
	T0TCR=0x01;
	while(T0TC<seconds);
	T0TCR|=0x03;
	T0TCR = 0x00;
}

void delay_milliseconds(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR|=0x03;
	T0TCR = 0x00;
}
