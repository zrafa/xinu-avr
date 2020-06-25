/* xsh_forever.c - xsh_forever */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_forever
 *------------------------------------------------------------------------
 */
shellcmd xsh_forever(int nargs, char *args[])
{

	for (;;);
		//sleep(1);

	return 0;
}
