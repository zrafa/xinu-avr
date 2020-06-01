/* Xinu for STM32
 *
 * Original license applies
 * Modifications for STM32 by Robin Krens
 * Please see LICENSE and AUTHORS 
 * 
 * $LOG$
 * 2019/11/11 - ROBIN KRENS
 * Initial version 
 * 
 * $DESCRIPTION$
 *
 * */

/* initialize.c - nulluser, sysinit */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

//RAFA
#include <serial_avr.h>
#include <avr/pgmspace.h>

/*
void probar_memoria() {

	char *m1;
	char *m2;
	char m3[] = "hola mundo";

	m1 = getmem(20);
	kprintf("m1 0x%08X , m3 0x%08X\n\n", m1, m3);
	strncpy(m1, m3, 10);
	kprintf("getmem %s \n", m1);
	kprintf("m1 0x%08X , m3 0x%08X\n\n", m1, m3);

}
*/


extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	process shell(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
extern 	int32 initintc(void);
void startup(int, struct procent *);		/* Process to finish startup tasks	*/

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

// RAFA 
// void PUT32 ( unsigned int, unsigned int );
// unsigned int GET32 ( unsigned int );
// void dummy ( unsigned int );

// #define GPIOCBASE 0x40011000
// #define RCCBASE 0x40021000


// FIN RAFA


void nullprocess(void) {

	// notmain();

	kprintf("nullp\n");
	
	// resume(create((void *)main, INITSTK, INITPRIO, "Main Process", 0, NULL));
	// 200 ok  and 400 ok
	resume(create((void *)shell, 200, INITPRIO, "shell", 0, NULL));
	
	for(;;);
}

// RAFA AVR specific:
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


//RAFA
#include <avr/interrupt.h>

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
		// kprintf("\n\r0x%8X, FreeMEM:%d", memptr, memptr->mlength);
	}
	
	kprintf("\n\rFreeMEM:%d\n", free_mem);

	/* Initialize the Null process entry */	
	int pid = create((void *)nullprocess, INITSTK, 10, "Null process", 0, NULL);

	struct procent * prptr = &proctab[pid];
	prptr->prstate = PR_CURR;
	
	/* Enable interrupts */
	enable();
	
	/* Initialize the real time clock */
	clkinit();
	

	/* Start of nullprocess */
	startup(0, prptr);

	for(;;);

}

/* Startup does a system call, the processor switches to handler 
 * mode and prepares for executing the null process (see syscall.c) 
 * This is also where a kernel mode to user mode switch can
 * take place */
void startup(int INIT, struct procent *p) {
	
	/* Should not be here, panic */
	// resume(INIT);
	nullprocess();

	avr_kprintf(m6);
	panic("");
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
	kprintf("\n\r%s\n", VERSION);

	/* Initialize free memory list */
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */
	prcount = 0;
//	prcount = 1;

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
