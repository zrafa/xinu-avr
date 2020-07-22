/* create.c - create, newpid */

/* avr specific */

#include <stdarg.h>
#include <xinu.h>

local	pid32 newpid();

#define	roundew(x)	( (x+3)& ~0x3)

/* avr specific */
#define	MAGIC		0xaa	/* unusual value for top of stk	*/


/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */
pid32	create(
	  int		(*procaddr)(),	/* procedure address		*/
	  int	ssize,		/* stack size in bytes		*/
	  int		priority,	/* process priority > 0		*/
	  char		*name,		/* name (for debugging)		*/
	  int	nargs,		/* number of args that follow	*/
	  ...
	)
{
	intmask 	mask;    	/* interrupt mask		*/
	pid32		pid;		/* stores new process id	*/
	struct	procent	*prptr;		/* pointer to proc. table entry */
	int i;
	unsigned char		*saddr;		/* stack address		*/
	va_list ap;

	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (int) roundew(ssize);
	if (((saddr = (unsigned char *)getstk(ssize)) ==
	     (uint32 *)SYSERR ) ||
	     (pid=newpid()) == SYSERR || priority < 1 ) {
		avr_kprintf(m10);
		restore(mask);
		return SYSERR;
	}


	
	prcount++;
	prptr = &proctab[pid];

	/* initialize process table entry for new process */
	prptr->prstate = PR_SUSP;	/* initial state is suspended	*/
	prptr->prprio = priority;
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE;

	/* set up initial device descriptors for the shell		*/
	prptr->prdesc[0] = CONSOLE;	/* stdin  is CONSOLE device	*/
	prptr->prdesc[1] = CONSOLE;	/* stdout is CONSOLE device	*/
	prptr->prdesc[2] = CONSOLE;	/* stderr is CONSOLE device	*/


	/* Initialize stack as if the process was called		*/
	*saddr-- = (char)MAGIC;		/* Bottom of stack */
	prptr->pargs = nargs;
	for (i=0 ; i<PNREGS ; i++)		// VER TAMANIO PARA AVR
		prptr->pregs[i] = INITREG;	
	prptr->paddr = (int *)procaddr;
	prptr->pregs[SPC_L] = lobyte((unsigned) procaddr); // GUARDAR SPC_L
	prptr->pregs[SPC_H] = hibyte((unsigned) procaddr);
	prptr->pregs[SSREG] = INITPS;
	// POR AHORA NO  (usado en kill.c en avr orig : prptr->pnxtkin = BADPID;
	// POR AHORA NO prptr->pdevs[0] = prptr->pdevs[1] = BADDEV;
	
	int * a = (int *)(&nargs + 1);
	for (i = 0; i < nargs; i++) {
		prptr->parg[i] = (int) *a++;
	}
	prptr->parg[nargs] = 0;
	
	/* machine/compiler dependent pass arguments to created process */
	prptr->pregs[24] = lobyte((unsigned)prptr->pargs);	/*r24*/
	prptr->pregs[25] = hibyte((unsigned)prptr->pargs);
	prptr->pregs[22] = lobyte((unsigned)&prptr->parg[0]);	/*r22*/
	prptr->pregs[23] = hibyte((unsigned)&prptr->parg[0]);

	*saddr-- = lobyte((unsigned)INITRET);	/* push on initial return address*/
	*saddr-- = hibyte((unsigned)INITRET);
	*saddr-- = lobyte((unsigned)procaddr);	/* push on procedure address	*/
	*saddr-- = hibyte((unsigned)procaddr);
	prptr->pregs[SSP_L] = lobyte((unsigned) saddr);
	prptr->pregs[SSP_H] = hibyte((unsigned) saddr);

	restore(mask);
	return pid;
}

/*------------------------------------------------------------------------
 *  newpid  -  Obtain a new (free) process ID
 *------------------------------------------------------------------------
 */
local	pid32	newpid(void)
{
	uint32	i;			/* iterate through all processes*/
//	static	pid32 nextpid = 1;	/* position in table to try or	*/
	static	pid32 nextpid = 0;	/* position in table to try or	*/
					/*  one beyond end of table	*/

	/* check all NPROC slots */

	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC;	/* wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}
	return (pid32) SYSERR;
}
