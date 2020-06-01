/* clkinit.c */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

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

	/* AVR atmega328p timer/clock init: interrupt every 1ms */

	TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
	TCCR0A |= (1<<WGM01);              //sets mode to CTC
	// OCR0A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable

	return;
}




unsigned int avr_ticks=0;

ISR(TIMER0_COMPA_vect)
{
	cli();

	/* Every ms: What TO DO */
	// clkhandler();


	avr_ticks ++;
	if (avr_ticks > 100) {
		avr_ticks=0;
		resched();
	}

	/* every second */
	/* if avr_ticks == 1000 then 1 second */

	sei();
}

