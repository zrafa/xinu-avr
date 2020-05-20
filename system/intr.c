/* Xinu for AVR
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

#include <xinu.h>
#include <avr/interrupt.h>


/* RAFA: the arguments and returns do not have any meaning. It were there
 * for STM32.
 * 
 * For AVR: remove them some day
 */

/*------------------------------------------------------------------------
 * disable  -  Disable interrupts and return the previous state
 *------------------------------------------------------------------------
 */
intmask disable() {
	cli();
	return 0;
}

/*------------------------------------------------------------------------
 * restore  -  Restore interrupts to value given by mask argument
   Cortex M3 hardware handles a lot, rewrite
 *------------------------------------------------------------------------
 */
inline void restore(intmask c) {
	sei();
}

/*------------------------------------------------------------------------
 * enable  -  Enable interrupts
 *------------------------------------------------------------------------
 */
inline void enable() {
	sei();
}

/*------------------------------------------------------------------------
 * pause or halt  -  Place the processor in a hard loop
 *------------------------------------------------------------------------
 */
inline void halt() {
	for (;;);
}

inline void pause() {
	for (;;);
}
