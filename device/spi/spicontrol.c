/* spicontrol.c - spicontrol */

#include <xinu.h>

/*------------------------------------------------------------------------
 * spicontrol  -  Control function for SPI device
 *------------------------------------------------------------------------
 */
devcall	spicontrol (
	struct	dentry	*devptr,	/* Entry in device switch table	*/
	int32	func,			/* Control function		*/
	int32	arg1,			/* Argument 1, if needed	*/
	int32	arg2			/* Argument 2, if needed	*/
	)
{
	struct	spi_csreg *csrptr;	/* SPI control and status regs	*/

	return OK;
}
