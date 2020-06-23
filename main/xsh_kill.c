/* xsh_kill.c - xsh_kill */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_kill - obtain and print the current month, day, year, and time
 *------------------------------------------------------------------------
 */
shellcmd xsh_kill(int nargs, char *args[]) {

	int32	retval;			/* return value			*/
	pid32	pid;			/* ID of process to kill	*/
	char	ch;			/* next character of argument	*/
	char	*chptr;			/* walks along argument string	*/

	/* Check argument count */

	if (nargs != 2) {
		return SYSERR;
	}

	/* compute process ID from argument string */

	chptr = args[1];
	ch = *chptr++;
	pid = 0;
	while(ch != NULLCH) {
		if ( (ch < '0') || (ch > '9') ) {
			return 1;
		}
		pid = 10*pid + (ch - '0');
		ch = *chptr++;
	}
	if (pid == 0) {
		return 1;
	}

	retval = kill(pid);
	if (retval == SYSERR) {
		//fprintf(stderr, "%s: cannot kill process %d\n",
		//	args[0], pid);
		return 1;
	}
	return 0;
}
