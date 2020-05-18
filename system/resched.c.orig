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

__attribute__ ((naked))
void resched(void)
{
	uint32 * restorestk;
	asm volatile("mrs r0, psp");
	asm volatile("stmdb r0!, {r4-r11}");
	asm volatile("mov %0, r0" : "=r" (restorestk)); // save tmp pointer

	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		asm volatile ("mov r0, %0" : : "r" (restorestk));
		asm volatile("ldmia r0!, {r4-r11} ");
		asm volatile ("msr psp, r0");
		asm volatile (
                	 "ldr r0, =0xFFFFFFFD" "\n\t"
	                 "mov lr, r0" "\n\t"
	                 "bx lr");
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			asm volatile ("mov r0, %0" : : "r" (restorestk));
			asm volatile("ldmia r0!, {r4-r11} ");
			asm volatile ("msr psp, r0");
		        asm volatile (
                	 "ldr r0, =0xFFFFFFFD" "\n\t"
	                 "mov lr, r0" "\n\t"
	                 "bx lr");
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/


	ptold->prstkptr = restorestk;
	
	/* Old process returns here when resumed */
	asm volatile ("mov r0, %0" : : "r" (ptnew->prstkptr));
	asm volatile("ldmia r0!, {r4-r11} ");
	asm volatile ("msr psp, r0");
        asm volatile (
                 "ldr r0, =0xFFFFFFFD" "\n\t"
                 "mov lr, r0" "\n\t"
                 "bx lr");
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
