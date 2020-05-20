/* init.c - init */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  init  -  Initialize a device and its driver
 *------------------------------------------------------------------------
 */
syscall	init(
	  did32		descrp		/* Descriptor for device	*/
	)
{
	intmask		mask;		/* Saved interrupt mask		*/
	struct dentry	*devptr;	/* Entry in device switch table	*/
	int32		retval;		/* Value to return to caller	*/

	kprintf("8\n");

	mask = disable();
	kprintf("8\n");
	if (isbaddev(descrp)) {
		kprintf("7\n");
		restore(mask);
		kprintf("6\n");
		return SYSERR;
	}
		kprintf("5\n");
	devptr = (struct dentry *) &devtab[descrp];
		kprintf("4\n");
	retval = (*devptr->dvinit) (devptr);
		kprintf("3\n");
	restore(mask);

	kprintf("8\n");
	return retval;
}
