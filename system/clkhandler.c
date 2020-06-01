/* clkhandler.c - clkhandler */

/* avr specific */

#include <xinu.h>

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */
void clkhandler()
{
	struct timer_csreg *tptr;

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
		resched();
	}
}
