/* meminit.c - meminit */

#include <xinu.h>

void	*minheap;	/* Start address of heap	*/
void	*maxheap;	/* End address of heap		*/

/*------------------------------------------------------------------------
 * meminit - Initialize the free memory list for BeagleBone Black
 *------------------------------------------------------------------------
 */

/* avr specific */
extern int __bss_end;

/* avr specific */
#define GET_FAR_ADDRESS(var)                          \
({                                                    \
    uint32_t tmp;                                     \
                                                      \
    __asm__ __volatile__(                             \
                                                      \
            "ldi    %A0, lo8(%1)"           "\n\t"    \
            "ldi    %B0, hi8(%1)"           "\n\t"    \
            "ldi    %C0, hh8(%1)"           "\n\t"    \
            "clr    %D0"                    "\n\t"    \
        :                                             \
            "=d" (tmp)                                \
        :                                             \
            "p"  (&(var))                             \
    );                                                \
    tmp;                                              \
})



void	meminit(void)
{
	struct	memblk *memptr;	/* Memory block pointer	*/

	/* avr specific */
        uint32 ptr_bss_end;
        ptr_bss_end = GET_FAR_ADDRESS(__bss_end);  //get the pointer

	/* Initialize the minheap and maxheap variables */

	minheap = ptr_bss_end+1;
	maxheap = 0x008008FF;	/* AVR atmega328p stack pointer when booting */

	/* Initialize the memory list as one big block */

	memlist.mnext = (struct memblk *)minheap;
	memptr = memlist.mnext;

	memptr->mnext = (struct memblk *)NULL;
	memlist.mlength = memptr->mlength =
		(uint32)maxheap - (uint32)minheap;
}
