/* printf.c - printf*/

#include <xinu.h>
#include <stdio.h>
#include <stdarg.h>

extern void _fdoprnt(char *, va_list, int (*)(did32, char), int);
extern int xinu_putc(did32, char);

/*------------------------------------------------------------------------
 *  printf  -  standard C printf function
 *------------------------------------------------------------------------
 */

#define PRINTF_BUF 81

int	printf(
	  const char		*fmt,
	  ...
	)
{

	char *c;
	char buf[PRINTF_BUF];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);

	c = buf;
	while(*c) {
		if(*c == '\n')
			putc(stdout, '\r');
		putc(stdout, *c);
		c++;
	};

	va_end(ap);
	return 0;
}
