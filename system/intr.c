/* intr.S - enable, disable, restore, halt, pause, (ARM) */

/* avr specific */

#include <xinu.h>
#include <avr/interrupt.h>

/*
 *  This code is based on AVR-Xinu by Michael Minor
 */

#include <avr/io.h>

/*------------------------------------------------------------------------
 * disable  -  Disable interrupts and return the previous state
 *------------------------------------------------------------------------
 */
intmask disable(void)
{
	int x = SREG;
	asm("cli");	/*and disable interrupts*/
	return x;
}

/*------------------------------------------------------------------------
 * restore  -  Restore interrupts to value given by mask argument
 *------------------------------------------------------------------------
 */
void restore(uint8 x)
{
	SREG = x;	/*restore the status register, possibly reenabling interrupts*/
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
