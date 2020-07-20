/* ex1.c - main */

#include <xinu.h>

/*------------------------------------------------------------------------
 * main  --  write "hi" on the console
 *------------------------------------------------------------------------
 */
void	main(void)
{
	putc(CONSOLE, 'h'); putc(CONSOLE, 'i');
	putc(CONSOLE, '\r'); putc(CONSOLE, '\n');
}
