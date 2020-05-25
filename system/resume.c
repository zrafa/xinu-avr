/* resume.c - resume */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resume  -  Unsuspend a process, making it ready
 *------------------------------------------------------------------------
 */
pri16	resume(
	  pid32		pid		/* ID of process to unsuspend	*/
	)
{


	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	pri16	prio;			/* Priority to return		*/

	mask = disable();
	if (isbadpid(pid)) {
// RAFA ACA ABORTA		notmain();
		kprintf("nores1\n");
		restore(mask);
		return (pri16)SYSERR;
	}
	prptr = &proctab[pid];
	if (prptr->prstate != PR_SUSP) {
		restore(mask);
		// kprintf("no resume 2%d\n", prptr->prstate);
		kprintf("nores2\n");
		return (pri16)SYSERR;
	}
	prio = prptr->prprio;		/* Record priority to return	*/

	kprintf("resume\n");
	ready(pid);
	restore(mask);
	return prio;
}
