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

/* clkhandler.c - clkhandler */

#include <xinu.h>

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */
void clkhandler()
{
	struct timer_csreg *tptr;
	tptr = (struct timer_csreg *)TIM2_BASE;

	/* Clear interrupt flag */

	tptr->sr &= ~(1 << TIM_UIF);

	/* Increment 1000ms counter */

	count1000++;

	/* After 1 sec, increment clktime */

	if(count1000 >= 1000) {
		clktime++;
		count1000 = 0;
	}

	/* check if sleep queue is empty */

	if(!isempty(sleepq)) {
		/* sleepq nonempty, decrement the key of */
		/* topmost process on sleepq		 */

		if((--queuetab[firstid(sleepq)].qkey) == 0) {

			wakeup();
		}
	}

	/* Decrement the preemption counter */
	/* Reschedule if necessary	    */

	if((--preempt) == 0) {
		preempt = QUANTUM;
		// PendSV call
		 *SCB_ICSR |= (1 << PENDSV_INTR);
	}
}
