/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent volatile *prptr;

	if (isbadpid(pid)) {
		kprintf("ready1\n");
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	
	kprintf("readyok\n");
	// *SCB_ICSR |= (1 << PENDSV_INTR);

	return OK;
}
