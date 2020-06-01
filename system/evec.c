/* evec.c -- initintc, set_evec	*/

typedef unsigned int size_t;
#include <avr/pgmspace.h>

#include <xinu.h>
#include <stdio.h>


/*------------------------------------------------------------------------
 * initintc - Initialize the Interrupt Controller
 *------------------------------------------------------------------------
 */
int32	initintc()
{
	return OK;
}

/*------------------------------------------------------------------------
 * set_evec - set exception vector to point to an exception handler
 *------------------------------------------------------------------------
 */
int32	set_evec(uint32 xnum, uint32 handler)
{
	/* There are only 92 interrupts allowed 0-2 */

	if(xnum > 92) {
		return SYSERR;
	}

	return OK;
}

