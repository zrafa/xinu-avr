/* clkhandler.c - clkhandler */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int avr_ticks=0;

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */

/* void clkhandler() */

ISR(TIMER0_COMPA_vect)
{

	/* Every ms */

	/* Increment 1000ms counter */

	count1000++;

	/* After 1 sec, increment clktime */

	if(count1000 >= 1000) {	/* previous was: if(count1000 >= 1000) */
		clktime++;
		count1000 = 0;
	}

	/* check if sleep queue is empty every 100ms */

	if ((count1000 % 100) == 0)	/* every 100ms */
		if(!isempty(sleepq)) {
			/* sleepq nonempty, decrement the key of */
			/* topmost process on sleepq             */

			if((--queuetab[firstid(sleepq)].qkey) == 0) {

				wakeup();
			}
		}

	/* our MCU is slow (16Mhz), so we do resched/preemption every 300ms */
	avr_ticks ++;
	if (avr_ticks > 300) {		
//	if (avr_ticks > 10) {		
//	if (avr_ticks > 100) {		
		avr_ticks=0;

		/* Decrement the preemption counter */
		/* Reschedule if necessary          */
		if((--preempt) == 0) {
			preempt = QUANTUM;
			resched();
		}
	}
}

