/* ramread.c  -  ramread */

#include <xinu.h>
#include <avr_eeprom_disk.h>

/*------------------------------------------------------------------------
 * eeprom_read  -  Read a block from a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_read (
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer to hold disk block	*/
	  int32	blk			/* Block number of block to read*/
	)
{
	int32	bpos;			/* Byte position of blk		*/

	bpos = RM_BLKSIZ * blk;
	// memcpy(buff, &Ram.disk[bpos], RM_BLKSIZ);
	eeprom_read_block(buff, bpos, RM_BLKSIZ);
	return OK;
}
