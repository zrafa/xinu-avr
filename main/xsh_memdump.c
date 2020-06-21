/* xsh_memdump.c - xsh_memdump */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

// RAFA
#include <avr/interrupt.h>

static void printnl(void)
{
	printf("\n\r");
}


/*------------------------------------------------------------------------
 * xsh_memdump - Print memory content
 *------------------------------------------------------------------------
 */
shellcmd xsh_memdump(int nargs, char *args[])
{

	int from = 0;
	int to = 0x8FF;		/* AVR atmega328p top RAM address */

	if (nargs == 3) {
		from = args[1];
		to = args[2];
	}

	long i;
	int j=0;
	char * c = 0;
	for (i = from; i < to ; i++) {
		c = (char *)i;
		if (j==0) {
			printf("\n");
			printf ("0x%08x  ", c);
		}
		j++;
		if (j==16) j=0;
		if (*c < 33)
			printf("-");
		else
			printf("%c", *c);
	}
	printnl();

	return 0;
}

