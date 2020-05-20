/* meminit.c - meminit */

#include <xinu.h>

void	*minheap;	/* Start address of heap	*/
void	*maxheap;	/* End address of heap		*/

/*------------------------------------------------------------------------
 * meminit - Initialize the free memory list for BeagleBone Black
 *------------------------------------------------------------------------
 */

//RAFA AGREGO ESTO
extern int __bss_end;



void	meminit(void)
{
	struct	memblk *memptr;	/* Memory block pointer	*/

	/* Initialize the minheap and maxheap variables */


	minheap = (void *)__bss_end+1;
	maxheap = (void *)__bss_end+1024; /* 1KB for AVR */

	// STM32 specific: minheap = (void *)&end;
	/* 1024 bytes is reserved for supervise mode handling */
	// STM32 specific: maxheap = (void *)MAXADDR - HANDLERSTACK;


	/* Initialize the memory list as one big block */

	memlist.mnext = (struct memblk *)minheap;
	memptr = memlist.mnext;

	memptr->mnext = (struct memblk *)NULL;
	memlist.mlength = memptr->mlength =
		(uint32)maxheap - (uint32)minheap;
}
