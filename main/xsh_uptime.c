/* xsh_uptime.c - xsh_uptime */
#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_uptime - shell to print the time the system has been up
 *------------------------------------------------------------------------
 */
shellcmd xsh_uptime(int nargs, char *args[])
{
	long	days, hrs, mins, secs;	/* days, hours, minutes,  and	*/
					/*  seconds since system boot	*/
	long	secperday = 86400;	/* seconds in a day		*/
	long	secperhr  =  3600;	/* seconds in an hour		*/
	long	secpermin =    60;	/* seconds in a minute		*/	

	/* Check for valid number of arguments */

	if (nargs > 1) {
		return 1;
	}

	secs = clktime;		/* total seconds since boot */

	/* subtract number of whole days */

	days  = secs/secperday;
	secs -= days*secperday;

	/* subtract number of hours */

	hrs   = secs/secperhr;
	secs -= hrs*secperhr;

	/* subtract number of minutes */

	mins  = secs/secpermin;
	secs -= mins*secpermin;

	printf("\r\n%d day(s) &", days);
	printf(" %dh:", hrs);
	printf("%dm:", mins);
	printf("%ds\r\n\n", secs);

	return 0;
}
