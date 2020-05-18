/* gpioinit.c - gpioinit */

#include <xinu.h>

struct	gpiocblk	gpiotab[NGPIO];

/*------------------------------------------------------------------------
 *  gpioinit  -  Initialize settings for a gpio device
 *------------------------------------------------------------------------
 */
devcall	gpioinit(
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	//struct gpio_csreg * csrptr;
	struct clock_csreg * clockptr;
	//struct gpiocblk * gpioptr;
	//csrptr = (struct gpio_csreg *)(devptr->dvcsr);
	clockptr = (struct clock_csreg *)CLOCK_BASE;
	//gpioptr = &gpiotab[devptr->dvminor];

	/* Enable clock on GPIO */
	switch (devptr->dvminor) {
		case 0:
			clockptr->apb2enr |= (1 << IOPAEN);
			break;
		case 1:
			clockptr->apb2enr |= (1 << IOPBEN);
			break;
		case 2:
			clockptr->apb2enr |= (1 << IOPCEN);
			break;
		case 3:
			clockptr->apb2enr |= (1 << IOPDEN);
			break;
		default:
			kprintf("Failed to recognize GPIO device");
			return SYSERR;
	}	

	return OK;
}
