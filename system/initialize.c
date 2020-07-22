/* initialize.c - nulluser, sysinit */

/* avr specific */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

/* avr specific */
#include <avr_serial.h>


/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
//local	process startup(void);	/* Process to finish startup tasks	*/
void startup(int INIT, struct procent *p);

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int32	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/* Control sequence to reset the console colors and cusor positiion	*/

#define	CONSOLE_RESET	" \033[0m\033[2J\033[;H"

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void nullprocess(void) {

	resume(create((void *)main, 440, INITPRIO, "main", 0, NULL));

	for(;;);
}

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


void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/

	/* Initialize the system */

	sysinit();

	/* avr specific */
	extern uint32 __bss_end, __data_start;
	uint32 ptr_bss_end;
	ptr_bss_end = GET_FAR_ADDRESS(__bss_end);  //get the pointer

	uint32 ptr_data_start;
	ptr_data_start = GET_FAR_ADDRESS(__data_start);  //get the pointer

	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("\nFreeMEM:%d (bytes)\n\n", free_mem);


	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/


	/* Initialize the Null process entry */	
	int pid = create((void *)nullprocess, INITSTK, 10, "nullp", 0, NULL);
	struct procent * prptr = &proctab[pid];
	prptr->prstate = PR_CURR;

	/* Enable interrupts */

	enable();
	
	/* create main without startup because:
 	 *  - startup is not needed so far 
	 *  - it fragments the free memory in two
	 */
	//resume(create((void *)main, 440, INITPRIO, "main", 0, NULL));

	/* Start of nullprocess */
	startup(0, prptr);


        /* Become the Null process (i.e., guarantee that the CPU has    */
        /*  something to run when no other process is ready to execute) */

	for(;;);

}

/*------------------------------------------------------------------------
 *
 * startup  -  Finish startup takss that cannot be run from the Null
 *		  process and then create and resumethe main process
 *
 *------------------------------------------------------------------------
 */
void startup(int INIT, struct procent *p)
// local process	startup(void)
{
	/* Create a process to execute function main() */

	//resume(create((void *)main, 440, INITPRIO, "main", 0, NULL));

	nullprocess();
	avr_kprintf(m6);
	panic("");

	/* Startup process exits at this point */

	return OK;
}



/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/


	/* Platform Specific Initialization */

	platinit();

	kprintf(CONSOLE_RESET);
	avr_kprintf(sysinit_m0);

	/* Initialize free memory list */

	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */
	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */	

/*
	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 1;
	prptr->prname[0] = 'n';
	prptr->prname[1] = 'u';
	prptr->prname[2] = 'l';
	prptr->prname[3] = 'l';
	prptr->prname[4] = 'p';
	prptr->prname[5] = 0;
*/
	// strncpy(prptr->prname, "prnull", 7);
/*
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
*/

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}


	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	
	for (i = 0; i < NDEVS; i++) {
		init(i);
	}

	return;
}

int32	stop(char *s)
{
	avr_kprintf(m12);
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
