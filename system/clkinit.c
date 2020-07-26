/* clkinit.c */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

uint32	clktime;		/* Seconds since boot			*/
unsigned long  count1000;	/* ms since last clock tick             */
qid16	sleepq;			/* Queue of sleeping processes		*/
unsigned long preempt;		/* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup
 *------------------------------------------------------------------------
 */
void clkinit(void)
{
	
	struct clock_csreg * clockptr;

	sleepq = newqueue();	/* Allocate a queue to hold the delta	*/
				/*   list of sleeping processes		*/
	preempt = QUANTUM;	/* Set the preemption time		*/
	clktime = 0;		/* Start counting seconds		*/
        count1000 = 0;


	/* 
         * AVR atmega328p timer/clock init: interrupt every 1ms 
	 * The AVR TIMER interrupt rutine is in clkhandler.c
         */
	TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
	TCCR0A |= (1<<WGM01);              //sets mode to CTC
	OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable

	return;
}

