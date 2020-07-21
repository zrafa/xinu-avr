/* kprintf.c -  kputc, kgetc, kprintf */
/* Kprintf uses a direct method to write to serial
 * Used for debugging purposes. Should in normal cases
 * use printf that does a syscall
 * */

#include <xinu.h>
#include <stdarg.h>

#include <avr_serial.h>

/*------------------------------------------------------------------------
 * kputc - use polled I/O to write a character to the console serial line
 *------------------------------------------------------------------------
 */
syscall kputc(
	  byte	c			/* character to write		*/
	)
{
	intmask mask;

	mask = disable();

	if (c == '\n')
		serial_put_char('\r');
	serial_put_char(c);

	restore(mask);
	return OK;
}

/*------------------------------------------------------------------------
 * kgetc - use polled I/O to read a character from the console serial line
 *------------------------------------------------------------------------
 */
syscall kgetc(void)
{
	// Not used
}

extern	void	_doprnt(char *, va_list, int (*)(int));




/*------------------------------------------------------------------------
 * kprintf  -  use polled I/O to print formatted output on the console
 *------------------------------------------------------------------------
 */
syscall kprintf(char *fmt, ...)
{
	va_list ap;
	//intmask mask;

	//mask = disable();

	char output[81];
	char *c;

	memset(output, 0, 81);
	va_start(ap, fmt);
	vsnprintf(output, 80, fmt, ap);
	va_end(ap);

	c = output;
	while(*c) {
		kputc(*c);
		c++;
	};

	//restore(mask);
        return OK;
}
