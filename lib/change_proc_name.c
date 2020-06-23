
#include <xinu.h>

void change_proc_name( char *name)
{
	struct	procent	*prptr;		/* pointer to proc. table entry */
	int i;


	prptr = &proctab[currpid];

	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
}

