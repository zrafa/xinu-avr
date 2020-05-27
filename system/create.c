/* create.c - create, newpid */

#include <stdarg.h>
#include <xinu.h>

local	pid32 newpid();

#define	roundew(x)	( (x+3)& ~0x3)


// RAFA
#define	MAGIC		0xaa	/* unusual value for top of stk	*/


/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */
pid32	create(
	  // void		*procaddr,	/* procedure address		*/
	  int		(*procaddr)(),	/* procedure address		*/
	  // uint32	ssize,		/* stack size in bytes		*/
	  int	ssize,		/* stack size in bytes		*/
	  // pri16		priority,	/* process priority > 0		*/
	  int		priority,	/* process priority > 0		*/
	  char		*name,		/* name (for debugging)		*/
	  // RAFA uint32	nargs,		/* number of args that follow	*/
	  int	nargs,		/* number of args that follow	*/
	  ...
	)
{
	intmask 	mask;    	/* interrupt mask		*/
	pid32		pid;		/* stores new process id	*/
	struct	procent	*prptr;		/* pointer to proc. table entry */
	int32		i;
	// uint32		*a;		/* points to list of args	*/
	// RAFA uint32		*saddr;		/* stack address		*/
	unsigned char		*saddr;		/* stack address		*/
	va_list ap;


	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	// ssize = (uint32) roundew(ssize);
	ssize = (int) roundew(ssize);
	// RAFA if (((saddr = (uint32 *)getstk(ssize)) ==
	if (((saddr = (unsigned char *)getstk(ssize)) ==
	     (uint32 *)SYSERR ) ||
	     (pid=newpid()) == SYSERR || priority < 1 ) {
		// kprintf("STK_ERR"); /* m10[] */
		avr_printf(m10);
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
//RAFA	uint32 * tmpstk;
//RAFA	uint32 * extraregs;
//RAFA	a = (uint32 *)(&nargs + 1);
//RAFA	tmpstk = ((uint32) saddr) - 0x1C;
//RAFA	extraregs = ((uint32) tmpstk) - 0x20; /* r4 - r11 */

//RAFA	for (int i = 0; i < nargs; i++) {
//RAFA		tmpstk[i] = (uint32) *a++;
//RAFA	}

//RAFA	tmpstk[5] = (uint32) userret;	/* LR */
//RAFA	tmpstk[6] = (uint32) procaddr; /* Function */
//RAFA	tmpstk[7] = (uint32) 0x01000000; /* Flag register */

	
//RAFA	for (int i = 0; i <= 7; i++) {
//RAFA		extraregs[i] = 0x0; /* Initialize to zero */
//RAFA	}
//RAFA	prptr->prstkptr = (char *)extraregs;

// RAFA AGREGA
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
	for (int i = 0; i < nargs; i++) {
		prptr->parg[i] = (int) *a++;
	}
/* RAFA ESTO ANDA
	va_start(ap,nargs);
	for (i=0 ; i < nargs; i++)
		{
	    prptr->parg[i] = va_arg(ap, unsigned int);
		}
	va_end(ap);
/* FIN RAFA ESTO ANDA */

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

	// kprintf("creat:%s\n",prptr->prname);
	// kprintf("crea.pid:%d %s\n",pid,name);
// RAFA FIN AGREGA
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
			// kprintf("\nnextpid NPROC: 0x%08X\n", NPROC);
			// kprintf("\nnextpid i: 0x%08X\n", i);
		if (proctab[nextpid].prstate == PR_FREE) {
			// kprintf("\nnextpid: 0x%08X\n", nextpid);
			return nextpid++;
		} else {
			nextpid++;
		}
	}
	return (pid32) SYSERR;
}
