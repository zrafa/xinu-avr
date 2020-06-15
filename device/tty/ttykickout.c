/* ttykickout.c - ttykickout */

#include <xinu.h>

#include <avr/interrupt.h>

/*------------------------------------------------------------------------
 *  ttykickout  -  "Kick" the hardware for a tty device, causing it to
 *		     generate an output interrupt (interrupts disabled)
 *------------------------------------------------------------------------
 */
void	ttykickout(
	 struct uart_csreg *csrptr	/* Address of UART's CSRs	*/
	)
{
	/* Force the UART hardware generate an output interrupt */

	cli();
	ttyhandler(1, 'X', 1);		/* 1, 'X' arguments useless  */
	sei();

	return;
}
