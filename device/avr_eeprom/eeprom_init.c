/* raminit.c  -  raminit */

#include <xinu.h>
#include <avr_eeprom_disk.h>

#define EEPROM_SIZE = 1024;

int eeprom_pos = 0;

/*------------------------------------------------------------------------
 *  eeprom_init  -  Initialize the eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_init (
	  const __flash struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	eeprom_pos = 0;

	return OK;
}
