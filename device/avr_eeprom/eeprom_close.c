/* ramclose.c  -  ramclose */

#include <xinu.h>

/*------------------------------------------------------------------------
 * eeprom_close  -  Close a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_close (
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	return OK;
}
