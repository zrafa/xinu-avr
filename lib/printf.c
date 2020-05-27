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
int	printf(
	  const char		*fmt,
	  ...
	)
{
//    va_list ap;
 //   //syscall putc(did32, char);
  //  int xinu_putc(did32, char);

   // va_start(ap, fmt);
    //_fdoprnt((char *)fmt, ap, putc, stdout);
    //va_end(ap);

   va_list ap;

        // RAFA
        char output[81];
        char *c;

        memset(output, 0, 81);
    va_start(ap, fmt);
     // RAFA _doprnt(fmt, ap, (int (*)(int))kputc);
    // vsnprintf(output, 80, fmt, ap);
    vsnprintf(output, 80, fmt, ap);
    va_end(ap);



        c = output;
        while(*c) {
               //  kputc(*c);
                putc(stdout, *c);
                c++;
        };
    //return OK;


    return 0;
}
