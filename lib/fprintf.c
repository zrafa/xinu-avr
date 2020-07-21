/* fprintf.c - _fdoprnt */

#include <xinu.h>
#include <stdarg.h>

extern void _fdoprnt(char *, va_list, int (*)(did32, char), int);

/*------------------------------------------------------------------------
 *  fprintf  -  Print a formatted message on specified device (file).
 *			Return 0 if the output was printed successfully,
 *			and -1 if an error occurred.
 *------------------------------------------------------------------------
 */
int	fprintf(
	  int		dev,		/* device to write to		*/
	  char		*fmt,		/* format string		*/
	  ...
	)
{
	syscall putc(did32, char);

	va_list ap;
        char output[81];
        char *c;

        memset(output, 0, 81);
	va_start(ap, fmt);
	vsnprintf(output, 80, fmt, ap);
	va_end(ap);

        c = output;
        while(*c) {
                putc(dev, *c);
                c++;
        };

	return 0;
}
