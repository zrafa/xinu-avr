/* getticks.c - getticks */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getticks  -  Retrieve the number of clock ticks since CPU reset
 *------------------------------------------------------------------------
 */
uint32  	getticks()
{
	/* Cortex M3 does have a clock cycle cnt register */
	uint32 ret = 0;
	return ret;
}
