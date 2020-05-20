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


extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
extern 	int32 initintc(void);
void startup(int, struct procent *);		/* Process to finish startup tasks	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
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
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define GPIOCBASE 0x40011000
#define RCCBASE 0x40021000

void notmain ( void )
{
    unsigned int ra;
    unsigned int rx;


//    ra=GET32(RCCBASE+0x18);
 //   ra|=1<<4; //enable port c
  //  PUT32(RCCBASE+0x18,ra);
    //config
   // ra=GET32(GPIOCBASE+0x04);
    //ra&=~(3<<20);   //PC13
//    ra|=1<<20;      //PC13
 //   ra&=~(3<<22);   //PC13
  //  ra|=0<<22;      //PC13
   // PUT32(GPIOCBASE+0x04,ra);

//    for(rx=0;rx<10;rx++)
 //   {
  //      PUT32(GPIOCBASE+0x10,1<<(13+0));
   //     for(ra=0;ra<200000;ra++) dummy(ra);
    //    PUT32(GPIOCBASE+0x10,1<<(13+16));
     //   for(ra=0;ra<200000;ra++) dummy(ra);
   // }
}

// FIN RAFA


void nullprocess(void) {

	notmain();

	
	
	resume(create((void *)main, INITSTK, INITPRIO, "Main Process", 0, NULL));
	
	for(;;);
}


//RAFA
#include <avr/interrupt.h>

char frase[] = "Xinu AVR loading...\n";
void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/

	//RAFA
	cli();	/* AVR disable interrups */
	blink_avr();

        // RAFA uartinit();
        serial_init();
        serial_put_char('A');
        serial_put_char('B');
	char f = serial_get_char();
	int c = atoi(&f);
        serial_put_char('X');
        serial_put_char(frase[c]);
        serial_put_str(frase);
	blink_avr();
	blink_avr();

	/* Initialize the system */

	sysinit();

	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	// RAFA kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

// RAFA 	kprintf("%10d bytes of Xinu code.\n",
// RAFA 		(uint32)&etext - (uint32)&text);
// RAFA 	kprintf("           [0x%08X to 0x%08X]\n",
// RAFA 		(uint32)&text, (uint32)&etext - 1);
// RAFA 	kprintf("%10d bytes of data.\n",
// RAFA 		(uint32)&ebss - (uint32)&data);
// RAFA 	kprintf("           [0x%08X to 0x%08X]\n\n",
// RAFA 		(uint32)&data, (uint32)&ebss - 1);


	/* Initialize the Null process entry */	
	int pid = create((void *)nullprocess, INITSTK, 10, "Null process", 0, NULL);

	struct procent * prptr = &proctab[pid];
	prptr->prstate = PR_CURR;
	
	/* Enable interrupts */
	enable();
	
	/* Initialize the real time clock */
	clkinit();
	
	//RAFA
	kprintf("\nstartup %s\n\n", VERSION);

	/* Start of nullprocess */
	startup(0, prptr);

	for(;;);

}

/* Startup does a system call, the processor switches to handler 
 * mode and prepares for executing the null process (see syscall.c) 
 * This is also where a kernel mode to user mode switch can
 * take place */
void startup(int INIT, struct procent *p) {
	
//	asm volatile (
//	         "push {r0}" "\n\t"
                 //"mov r0, 0x3" "\n\t"  // kernel to user mode switch 
                 //"msr control, r0" "\n\t"  
                 //"isb" "\n\t"
  //               "pop {r0}" );
 //       asm volatile("svc 1");

	/* Should not be here, panic */
	// RAFA panic("Can't startup system"); 
	panic(&m6[0]); 
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
	kprintf("\n%s\n\n", VERSION);


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
	kprintf("%s\n", s);
//	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
