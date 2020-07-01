/* xsh_ps.c - xsh_ps */

#include <xinu.h>
#include <stdio.h>

const __flash char ps_msg0[] = "\ntable of current processes\n";
const __flash char ps_msg1[] = "\nname\tid\tparent\tprio\tstate\tstklen\tsem waits\n--\n";

/*------------------------------------------------------------------------
 * xsh_ps - show processes
 *------------------------------------------------------------------------
 */
shellcmd xsh_ps(int nargs, char *args[])
{
	int32	i;			/* walks through args array	*/

        /* check all NPROC slots */

	printf("%S", ps_msg0);
	printf("%S", ps_msg1);
        for (i = 0; i < NPROC; i++) {
		if (proctab[i].prstate == PR_FREE)
			continue;
		printf("%s\t%d", proctab[i].prname, i);
		printf("\t%d ", proctab[i].prparent);
		printf("\t%d ", proctab[i].prprio);
		printf("\t%d ", proctab[i].prstate);
		printf("\t%d ", proctab[i].prstklen);
		printf("\t%d ", proctab[i].prsem);
		printf("\n");
	}


	return 0;
}
