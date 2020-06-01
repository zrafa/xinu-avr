/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/* avr specific */

int resched(void)
{
	register struct procent volatile *ptold;	/* Ptr to table entry for old process	*/
	register struct procent volatile *ptnew;	/* Ptr to table entry for new process	*/
	int newpid;

	preempt = QUANTUM;		/* reset preemption counter	*/

	/* no switch needed if current process priority higher than next */
	
	ptold = (struct pentry *)&proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			// kprintf("resch no %s\n", ptold->prname);
			return (OK);
		}

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* remove highest priority process at end of ready list */
	
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;

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
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
