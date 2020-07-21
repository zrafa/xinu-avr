/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/* avr specific */

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	register struct procent volatile *ptold;	/* Ptr to table entry for old process	*/
	register struct procent volatile *ptnew;	/* Ptr to table entry for new process	*/
	int newpid;

	// RAFA
//	kprintf("POR ACA\n");
	/* If rescheduling is deferred, record attempt and return */

	//kprintf("n:%d\n",Defer.ndefers);
	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	//kprintf("POR ACA2\n");
	/* Point to process table entry for the current (old) process */
	
	////kprintf("cp:%d\n",currpid);
	//kprintf("poio:%d\n",ptold->prprio);
	//kprintf("read:%d\n", firstkey(readylist));
	ptold = (struct pentry *)&proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
	//kprintf("POR ACA3\n");
			return;
		}

	//kprintf("POR ACA4\n");
		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	//kprintf("POR ACA5\n");
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->pregs[0],&ptnew->pregs[0]);	/* switch context from old to new */

	/* Old process returns here when resumed */

	return;
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
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
