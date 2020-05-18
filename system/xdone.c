/* xdone.c - xdone */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  xdone  -  Print system completion message as last process exits
 *------------------------------------------------------------------------
 */
void	xdone(void)
{
	// RAFA kprintf("\n\nAll user processes have completed.\n\n");
	kprintf(&m3[0]);
	halt();				/* Halt the processor		*/
}
