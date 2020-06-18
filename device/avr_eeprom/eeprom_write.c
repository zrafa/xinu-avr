/* ramwrite.c  -  ramwrite */

#include <xinu.h>
#include <avr_eeprom_disk.h>

/*------------------------------------------------------------------------
 * eeprom_write  -  Write a block to a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_write (
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer containing a block	*/
	  int32	blk			/* Block number to write	*/
	)
{
	int32	bpos;			/* Byte position of blk		*/

	bpos = RM_BLKSIZ * blk;
	// memcpy(&Ram.disk[bpos], buff, RM_BLKSIZ);
	eeprom_write_block(buff, bpos, RM_BLKSIZ);
	return OK;
}
