/* raminit.c  -  raminit */

#include <xinu.h>
#include <avr_eeprom_disk.h>

// struct	ramdisk	Ram;

/*------------------------------------------------------------------------
 *  eeprom_init  -  Initialize the eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_init (
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	/*
	memcpy(Ram.disk, "hopeless", 8);
	memcpy( &Ram.disk[8], Ram.disk, RM_BLKSIZ * RM_BLKS - 8);
	*/
	return OK;
}
