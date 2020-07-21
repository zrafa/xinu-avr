/* platinit.c - platinit */

/* avr specific */


#include <xinu.h>

/* avr specific */
#include <avr/interrupt.h>
#include <avr_serial.h>


/*------------------------------------------------------------------------
 * platinit - platform specific initialization
 *------------------------------------------------------------------------
 */

void platinit(void)
{

	/* avr specific */
	cli();	/* AVR disable interrups */

	blink_avr();
	blink_avr();

	/* avr uart init */
        serial_init();

	/* Initialize the Interrupt Controller (evec.c) */
	initintc();

	/* System calls */
	// syscall_init();
}

