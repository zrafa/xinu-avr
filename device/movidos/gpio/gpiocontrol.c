/* gpiocontrol.c - gpiocontrol */

#include <xinu.h>

#define OFFSETMODE(x)	(x * 4)
#define OFFSETCFG(x) 	((x * 4) + 2)
#define OFFSETMODE2(x)	((x - 8) * 4) 
#define OFFSETCFG2(x) 	(((x - 8) * 4) + 2)

static int setmode(struct dentry * devptr, uint32 mode, uint32 pin) 
{	
	struct gpio_csreg * csrptr;
	csrptr = (struct gpio_csreg *)(devptr->dvcsr);

	if (pin < 8) {
	csrptr->crl &= ~(0x3 << OFFSETMODE(pin)); // clear
	csrptr->crl |= (mode << OFFSETMODE(pin)); 
	}

	else {
	csrptr->crh &= ~(0x3 << OFFSETMODE2(pin)); // clear
	csrptr->crh |= (mode << OFFSETMODE2(pin)); 
	}
	return 0;
}

static int setcnf(struct dentry * devptr, uint32 mode, uint32 pin) 
{
	struct gpio_csreg * csrptr;
	csrptr = (struct gpio_csreg *)(devptr->dvcsr);

	if (pin < 8) {
	csrptr->crl &= ~(0x3 << OFFSETCFG(pin)); // clear
	csrptr->crl |= (mode << OFFSETCFG(pin)); 
	}
	else {
	csrptr->crh &= ~(0x3 << OFFSETCFG2(pin)); // clear
	csrptr->crh |= (mode << OFFSETCFG2(pin)); 
	}
	return 0;
}

/*------------------------------------------------------------------------
 *  gpiocontrol  -  Control a gpio device pin settings
 *------------------------------------------------------------------------
 */
devcall gpiocontrol(struct dentry * devptr, int32 func, int32 mode, int32 pin) {

	switch(func) {

		case SETMODE: 
			setmode(devptr, mode, pin);
			break;
		case SETCFG:
			setcnf(devptr, mode, pin);
			break;

		default:
			break;

	}
	return OK;

}
