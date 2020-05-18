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

/* clkinit.c - clkinit STM32 */

#include <xinu.h>

uint32	clktime;		/* Seconds since boot			*/
uint32  count1000;              /* ms since last clock tick             */
qid16	sleepq;			/* Queue of sleeping processes		*/
uint32	preempt;		/* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup
 *------------------------------------------------------------------------
 */
void clkinit(void)
{
	
	struct clock_csreg * clockptr;
	struct timer_csreg * tptr;
	clockptr = (struct clock_csreg *)CLOCK_BASE;
	tptr = (struct timer_csreg *)TIM2_BASE;

	sleepq = newqueue();	/* Allocate a queue to hold the delta	*/
				/*   list of sleeping processes		*/
	preempt = QUANTUM;	/* Set the preemption time		*/
	clktime = 0;		/* Start counting seconds		*/
        count1000 = 0;

	/* Enable timer peripheral */
	clockptr->apb1enr |= (1 << TIM2EN);
	
	/* Configuration for 1ms interrupt timer 
	Based on 8 MHz chip CLK / 2 */
	tptr->cr1 |= (1 << TIM_URS);
	tptr->psc = 0x7; /* Set to 0x3 for 1Mhz */
	tptr->arr = 0x1000; /* Set to 1000 */
	tptr->dier |= 0x1; /* Enable interrupts */

	/* Set interrupt vector for timer */
	set_evec(TIM2_IRQ, (uint32)clkhandler);
	*NVIC_ISER0 |= (1 << 28);

	/* Set interrupt for PendSV: a pendsv call will execute the scheduler  */
	set_evec(PENDSV_ENTRY, (uint32)resched);

	/* Enable and start timer */
	tptr->cr1 |= (1 << TIM_CEN);
	
	return;
}
