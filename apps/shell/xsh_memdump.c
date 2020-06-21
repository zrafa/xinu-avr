/* xsh_memstat.c - xsh_memstat */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

// RAFA
#include <avr/interrupt.h>


static	void	printMemUse(void);
static	void	printFreeList(void);

static void printnl(void)
{
	printf("\n\r");
}


/*------------------------------------------------------------------------
 * xsh_memstat - Print statistics about memory use and dump the free list
 *------------------------------------------------------------------------
 */
shellcmd xsh_memstat(int nargs, char *args[])
{


//	printMemUse();
	printFreeList();


	return 0;
}


/*------------------------------------------------------------------------
 * printFreeList - Walk the list of free memory blocks and print the
 *			location and size of each
 *------------------------------------------------------------------------
 */
static void printFreeList(void)
{
//	char t[80];
	struct memblk *block;

	/* Output a heading for the free list */

//	printf("Free:\n");
	printf("FreeMEM: addr len\n");
	
	// avr_printf(m11);
	for (block = memlist.mnext; block != NULL; block = block->mnext) {
		printf("0x%08x %d\n", block,
			(uint32) block->mlength);
	}

	long i;
	int j=0;
	char * c = 0;
	for (i=0; i<0x5bd ; i++) {
		c = (char *)i;
		if (j==0) {
			serial_put_char('\n');
			serial_put_char('\r');
			printf ("0x%08x  ", c);
		}
		j++;
		if (j==16) j=0;
		if (*c < 33)
			serial_put_char('-');
		else
			serial_put_char(*c);
	}
	printnl();
}

extern void start(void);
extern void *_end;

/*------------------------------------------------------------------------
 * printMemUse - Print statistics about memory use
 *------------------------------------------------------------------------
 */
static void printMemUse(void)
{
	int i;				/* Index into process table	*/
	uint32 code = 0;		/* Total Xinu code memory	*/
	uint32 stack = 0;		/* Total used stack memory	*/
	uint32 kheap = 0;		/* Free kernel heap memory	*/
	uint32 kfree = 0;		/* Total free memory		*/
	struct memblk *block;	 	/* Ptr to memory block		*/

	/* Calculate amount of text memory */

//	code = (uint32)&etext - (uint32)&text;

	/* Calculate amount of allocated stack memory */
	/*  Skip the NULL process since it has a private stack */

	for (i = 0; i < NPROC; i++) {
		if (proctab[i].prstate != PR_FREE) {
			stack += (uint32)proctab[i].prstklen;
		}
	}

	/* Calculate the amount of memory on the free list */

	for (block = memlist.mnext; block != NULL; block = block->mnext) {
		kfree += block->mlength;
	}

	/* Calculate the amount of free kernel heap memory */

	kheap = kfree - stack;

	/* Output statistics on current memory use */

//	printf("code: %10d\n", (uint32) code);
//	printf("stack:%10d bytes\n", (uint32) stack);
//	printf("kernel stk:%10d bytes\n", (uint32) mspstack);
//	printf("heap:%10d bytes\n\n", (uint32) kheap);
}
