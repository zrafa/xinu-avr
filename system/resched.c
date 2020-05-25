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

/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/* Reschedule is implemented on Cortex's PendSV call
 * The __attribute__((naked)) makes sure the compiler doesn't
 * places registers on the stack
 *
 * A PendSV is similar to an exception or interrupt
 * A stack frame is pushed on entry and popped
 * on exit BY PROCESSOR. */

/* A pendSV call before entering this handler
 * places the following on the stack 
 * 
 * R0 <- args[0]
 * R1 <- args[1]
 * R2 
 * R3
 * R12
 * LR <- Not a real LR, A certain 'mask'
 * PC 
 * PSR <- Status of processor before call
 *
 * */

// RAFA __attribute__ ((naked))
// RAFA void resched(void)
// RAFA {
// RAFA 	uint32 * restorestk;
/*
	asm volatile("mrs r0, psp");
	asm volatile("stmdb r0!, {r4-r11}");
	asm volatile("mov %0, r0" : "=r" (restorestk)); // save tmp pointer

*/
// RAFA 	struct procent *ptold;	/* Ptr to table entry for old process	*/
// RAFA 	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

// RAFA 	if (Defer.ndefers > 0) {
/*
		Defer.attempt = TRUE;
		asm volatile ("mov r0, %0" : : "r" (restorestk));
		asm volatile("ldmia r0!, {r4-r11} ");
		asm volatile ("msr psp, r0");
		asm volatile (
                	 "ldr r0, =0xFFFFFFFD" "\n\t"
	                 "mov lr, r0" "\n\t"
	                 "bx lr");
*/
// RAFA 	}

	/* Point to process table entry for the current (old) process */

//RAFA		ptold = &proctab[currpid];

//RAFA		if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
//RAFA			if (ptold->prprio > firstkey(readylist)) {
//RAFA				return (OK);
//RAFA			}
/*
			asm volatile ("mov r0, %0" : : "r" (restorestk));
			asm volatile("ldmia r0!, {r4-r11} ");
			asm volatile ("msr psp, r0");
		        asm volatile (
                	 "ldr r0, =0xFFFFFFFD" "\n\t"
	                 "mov lr, r0" "\n\t"
	                 "bx lr");
*/
// RAFA 		}

		/* Old process will no longer remain current */

//RAFA			ptold->prstate = PR_READY;
//RAFA			insert(currpid, readylist, ptold->prprio);
//RAFA		}

	/* Force context switch to highest priority ready process */

	
// RAFA 	currpid = dequeue(readylist);
// RAFA 	ptnew = &proctab[currpid];
// RAFA 	ptnew->prstate = PR_CURR;
// RAFA 	preempt = QUANTUM;		/* Reset time slice for process	*/


// RAFA 	ptold->prstkptr = restorestk;
	
	/* Old process returns here when resumed */
/*
	asm volatile ("mov r0, %0" : : "r" (ptnew->prstkptr));
	asm volatile("ldmia r0!, {r4-r11} ");
	asm volatile ("msr psp, r0");
        asm volatile (
                 "ldr r0, =0xFFFFFFFD" "\n\t"
                 "mov lr, r0" "\n\t"
                 "bx lr");
*/


// RAFA }
/*
print_free_mem() {

	struct	memblk	*memptr;
	uint32	free_mem;		

	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	 kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	   kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, (uint32)memptr);
	    kprintf("           [0x%08X ]\n",
		(uint32)memptr + memptr->mlength - 1);
	}


}
*/

int resched(void)
{
	// register struct	pentry volatile *ptold;	/* pointer to old process entry */
	// register struct	pentry volatile *nptr;	/* pointer to new process entry */
	register struct procent volatile *ptold;	/* Ptr to table entry for old process	*/
	register struct procent volatile *ptnew;	/* Ptr to table entry for new process	*/
	int newpid;

	// print_free_mem();
	preempt = QUANTUM;		/* reset preemption counter	*/

	serial_put_char('X');
	/* no switch needed if current process priority higher than next */
	
		ptold = (struct pentry *)&proctab[currpid];

		if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
			if (ptold->prprio > firstkey(readylist)) {
				kprintf("resch no %s\n", ptold->prname);
				return (OK);
			}

			ptold->prstate = PR_READY;
			insert(currpid, readylist, ptold->prprio);
		}
//RAFA	if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
     //RAFA        ( lastkey(rdytail) < optr->pprio) )	{
//		kprintf("resched: No Switch currpid=%d\n", currpid);
	//RAFA	return(OK);
	//RAFA}
	
	/* force context switch */
//RAFA	if (optr->pstate == PRCURR) {
//RAFA		optr->pstate = PRREADY;
//RAFA		insert(currpid,rdyhead,optr->pprio);
//RAFA	}

	/* remove highest priority process at end of ready list */
	
		currpid = dequeue(readylist);
		ptnew = &proctab[currpid];
		ptnew->prstate = PR_CURR;

//	if ( (newpid = getlast(rdytail)) == EMPTY )
//		return(EMPTY);
	
//	nptr = &proctab[ ( currpid = newpid ) ];
//	nptr->pstate = PRCURR;		/* mark it currently running	*/
//	kprintf("resched: Yes Switch currpid=%d\n", currpid);

//	kprintf("ctxs %s\n", ptnew->prname);
	serial_put_char('W');
//	if ((*ptnew->prname) == 's')
//		serial_put_char('S');
//	serial_put_char(*ptold->prname);;
	ctxsw(&ptold->pregs[0],&ptnew->pregs[0]);	/* switch context from old to new */

	return(OK);
}


/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			*SCB_ICSR |= (1 << PENDSV_INTR);
		}
		return OK;

	    default:
		return SYSERR;
	}
}
