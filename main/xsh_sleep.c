/* xsh_sleep.c - xsh_sleep */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_sleep  -  Shell command to delay for a specified number of seconds
 *------------------------------------------------------------------------
 */
shellcmd xsh_sleep(int nargs, char *args[])
{
	int32	delay;			/* Delay in seconds		*/
	char	*chptr;			/* Walks through argument	*/
	char	ch;			/* Next character of argument	*/

	/* Check for valid number of arguments */

	if (nargs != 2) {
		return 1;
	}

	chptr = args[1];
	ch = *chptr++;
	delay = 0;
	while (ch != NULLCH) {
		if ( (ch < '0') || (ch > '9') ) {
	//		fprintf(stderr, "%s: nondigit in argument\n",
	//			args[0]);
			return 1;
		}
		delay = 10*delay + (ch - '0');
		ch = *chptr++;
	}
	sleep(delay);
	return 0;
}
