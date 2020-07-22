/* ramclose.c  -  ramclose */

#include <xinu.h>

/*------------------------------------------------------------------------
 * eeprom_close  -  Close a eeprom disk
 *------------------------------------------------------------------------
 */
devcall	eeprom_close (
	 const __flash struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	return OK;
}
