#include <xinu.h>

extern serial_put_char(char);

void avr_kprintf(const __flash char m[])
{
	int i;
	for (i=0; i<strlen_P(m); i++)
		serial_put_char(m[i]);
}

