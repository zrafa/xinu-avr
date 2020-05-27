#include <xinu.h>

void avr_printf(char mess[])
{
	char t[80];

	memset(t, 80, 0);
	strncpy_P(t, mess, 79);
	printf("%s", t);
}
