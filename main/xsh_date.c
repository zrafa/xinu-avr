/* xsh_date.c - xsh_date */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_date - set or get the date and time
 *------------------------------------------------------------------------
 */
shellcmd xsh_date(int nargs, char *args[])
{
	char avr_date[80];

	if (nargs == 1) {
		get_date(avr_date);
  		printf("\n%s\n\n", avr_date);
		return 0;
	} 

	if (nargs != 3)
		return -1;
	
	set_date(args[1], args[2]);

	return 0;
}
