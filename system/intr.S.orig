/* Xinu for STM32
 *
 * Original license applies
 * Modifications for STM32 by Robin Krens
 * Please see LICENSE and AUTHORS 
 * 
 * $LOG$
 * 2019/11/11 - ROBIN KRENS
 * Initial version 
 * 
 * $DESCRIPTION$
 *
 * */

/* intr.S - enable, disable, restore, halt, pause, (ARM) */

#include <cortexm3.h>

	.text
	.globl	disable
	.globl	restore
	.globl	enable
	.globl	pause
	.globl	halt

/*------------------------------------------------------------------------
 * disable  -  Disable interrupts and return the previous state
 *------------------------------------------------------------------------
 */
disable:
	mrs	r0, psr		/* Copy the CPSR into r0		*/
	cpsid	i		/* Disable interrupts			*/
	bx	lr		/* Return the CPSR			*/

/*------------------------------------------------------------------------
 * restore  -  Restore interrupts to value given by mask argument
   Cortex M3 hardware handles a lot, rewrite
 *------------------------------------------------------------------------
 */
restore:
	msr	psr_nzcvq, r0	/* Restore the CPSR			*/
	cpsie	i		
	bx 	lr		/* Return to caller			*/

/*------------------------------------------------------------------------
 * enable  -  Enable interrupts
 *------------------------------------------------------------------------
 */
enable:
	cpsie	i		/* Enable interrupts			*/
	bx	lr		/* Return				*/

/*------------------------------------------------------------------------
 * pause or halt  -  Place the processor in a hard loop
 *------------------------------------------------------------------------
 */
halt:
pause:
	cpsid	i		/* Disable interrupts		*/
dloop:	b	dloop		/* Dead loop			*/
