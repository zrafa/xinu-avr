/* platinit.c - platinit */

/* avr specific */


#include <xinu.h>

/* avr specific */
#include <avr/interrupt.h>
#include <serial_avr.h>


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
	char f = serial_get_char();

	/* Initialize the Interrupt Controller (evec.c) */
	initintc();

	/* System calls */
	syscall_init();
}

