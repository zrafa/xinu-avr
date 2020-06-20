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

/*
	va_list ap;

        char output[81];
        char *c;

        memset(output, 0, 81);
	va_start(ap, fmt);
	vsnprintf(output, 80, fmt, ap);
	va_end(ap);

        c = output;
        while(*c) {
               //  kputc(*c);
                putc(stdout, *c);
                c++;
        };
*/


  
  char buf[PRINTF_BUF];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  for(char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
  {
    if(*p == '\n')
    {
      putchar('\r');
    }
    putchar(*p);
  }
  va_end(ap);
	return 0;
}
