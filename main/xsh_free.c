/* xsh_free.c - xsh_free */

#include <xinu.h>
#include <stdio.h>

const __flash char free_msg0[] = "\nfree mem list:\n\raddr\t\tlen\n";
const __flash char free_msg1[] = "\n\t\ttotal\tused\tfree\nSRAM Mem\t";

/*------------------------------------------------------------------------
 * xsh_free - show free memory available
 *------------------------------------------------------------------------
 */
shellcmd xsh_free(int nargs, char *args[])
{
	int32	i;			/* walks through args array	*/
	long free_mem;
	struct memblk *block;

        printf("%S", free_msg0);

        /* Output Xinu memory layout */
        free_mem = 0;
        for (block = memlist.mnext; block != NULL;
                                                block = block->mnext) {
                free_mem += block->mlength;

		printf("0x%08x\t%d\n", block,
                        (uint32) block->mlength);
        }

	printf("%S", free_msg1);
	printf("%d\t%d\t%d\n", maxheap, maxheap-free_mem, free_mem);

	return 0;
}
