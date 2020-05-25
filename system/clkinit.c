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


/* RAFA : LO QUE SIGUE ERA PARA el CLOCK STM32 */
	/* Enable timer peripheral */
// RAFA	clockptr->apb1enr |= (1 << TIM2EN);
	
	/* Configuration for 1ms interrupt timer 
	Based on 8 MHz chip CLK / 2 */
// RAFA	tptr->cr1 |= (1 << TIM_URS);
// RAFA	tptr->psc = 0x7; /* Set to 0x3 for 1Mhz */
// RAFA	tptr->arr = 0x1000; /* Set to 1000 */
// RAFA	tptr->dier |= 0x1; /* Enable interrupts */

	/* Set interrupt vector for timer */
// RAFA	set_evec(TIM2_IRQ, (uint32)clkhandler);
// RAFA	*NVIC_ISER0 |= (1 << 28);

	/* Set interrupt for PendSV: a pendsv call will execute the scheduler  */
// RAFA	set_evec(PENDSV_ENTRY, (uint32)resched);

	/* Enable and start timer */
// RAFA	tptr->cr1 |= (1 << TIM_CEN);
	
/* AVR atmega328p timer/clock init: interrupt every 1ms */

    // cli();         // We are here with interrupts disablled */
    TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
    TCCR0A |= (1<<WGM01);              //sets mode to CTC
    // OCR0A = 0x7C;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
    OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
    TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable
    // sei();                             //enable global interrupts

	return;
}




unsigned long avr_ticks=0;

ISR(TIMER0_COMPA_vect)
{
     cli();

	/* Every ms: What TO DO */
	//clkhandler();


    avr_ticks ++;
    if (avr_ticks > 100) {
//	/* every second */
	avr_ticks=0;
	resched();
    }

 //   resched();
    sei();
}

