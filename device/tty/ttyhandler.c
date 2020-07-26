/* ttyhandler.c - ttyhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  ttyhandler  -  Handle an interrupt for a tty (serial) device
 *------------------------------------------------------------------------
 */
void ttyhandler(uint32 xnum, char c, int flag) {
	const __flash struct	dentry	*devptr;	/* Address of device control blk*/
	struct	ttycblk	*typtr;		/* Pointer to ttytab entry	*/	
	struct	uart_csreg *csrptr;	/* Address of UART's CSR	*/

	/* Get CSR address of the device (assume console for now) */

	devptr = (struct dentry *) &devtab[CONSOLE];

	/* Obtain a pointer to the tty control block */

	typtr = &ttytab[devptr->dvminor];

	/* Test type of UART interrupt */

	/* AVR */

	if (flag) 	/* TX */
		ttyhandle_out(typtr, csrptr);
	else		/* RX */
		ttyhandle_in(typtr, csrptr, c);

}
