/* xsh_reboot.c - xsh_reboot */

#include <xinu.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

/*------------------------------------------------------------------------
 * xsh_reboot - reset Xinu system. WARNING: this is not a hardware reset
 *------------------------------------------------------------------------
 */
shellcmd xsh_reboot(int nargs, char *args[])
{
	void(* reset_func) (void) = 0;//declare reset function at address 0
	cli(); // disable interrupts
	reset_func();
}
