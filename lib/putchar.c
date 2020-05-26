/* putchar.c - putchar */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  putchar  -  C putchar function
 *------------------------------------------------------------------------
 */
int	putchar(
	  int		c
	)
{
    // RAFA return fputc(c, stdout);
    serial_put_char(c);
	return 0;
}
