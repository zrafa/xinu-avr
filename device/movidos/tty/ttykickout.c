/* ttykickout.c - ttykickout */

#include <xinu.h>

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
	csrptr->cr1 |= (1 << UART_INTR_TX);
	*NVIC_STIR = 0x25; /* Generate general UART interrupt */

	return;
}
