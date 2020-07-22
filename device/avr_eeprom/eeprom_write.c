/* ramwrite.c  -  ramwrite */

#include <xinu.h>
#include <avr_eeprom_disk.h>

/*------------------------------------------------------------------------
 * eeprom_write  -  Write a block to a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_write (
	  const __flash struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer containing a block	*/
	  uint32 count 			/* Count of bytes to write */
	)
{

	if (eeprom_pos + count >= EEPROM_SIZE)
		return SYSERR;

	eeprom_write_block((void *)buff, (const void *)eeprom_pos, count);

	eeprom_pos = eeprom_pos + count;

	return OK;
}
