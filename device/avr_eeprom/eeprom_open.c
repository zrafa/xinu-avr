/* ramopen.c  -  ramopen */

#include <xinu.h>

/*------------------------------------------------------------------------
 * eeprom_open  -  Open a eeprom disk
 *------------------------------------------------------------------------
 */

devcall	eeprom_open (
	 const __flash struct	dentry	*devptr,	/* Entry in device switch table	*/
	 char	*name,			/* Unused for a ram disk	*/
	 char	*mode			/* Unused for a ram disk	*/
	)
{
	/* No action -- just return the device descriptor */

	//RAFA
		kprintf("eou:%i\n",devptr->dvnum);
	return devptr->dvnum;
}
