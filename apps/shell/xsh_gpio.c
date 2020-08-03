/* xsh_gpio.c - xsh_gpio */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_gpio - write a value v in port p
 *------------------------------------------------------------------------
 *
 * Two modes:
 * Normal mode. Example: gpio b 32		# arduino pin 13 high
 * Extra Arduino mode. Example: gpio 13 1	# arduino pin 13 high
 */
shellcmd xsh_gpio(int nargs, char *args[])
{
	char p;
	unsigned char v;

	char pin;
	unsigned char val;


	/* Normal mode. Example: gpio b 32	# arduino pin 13 high */

	p = *args[1];
	v = number(args[2]);

	if ((p == 'b') | (p == 'c') | (p == 'd')) {
		gpio_write(p, v);
		return 0;
	}

	/* Extra arduino mode. Example: gpio 13 1 # arduino pin 13 high */

	pin = number(args[1]);
	gpio_arduino_write(pin, v);

	return 0;
}

