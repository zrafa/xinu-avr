/* kprintf.c -  kputc, kgetc, kprintf */
/* Kprintf uses a direct method to write to serial
 * Used for debugging purposes. Should in normal cases
 * use printf that does a syscall
 * */

#include <xinu.h>
#include <stdarg.h>

#include <serial_avr.h>

/*------------------------------------------------------------------------
 * kputc - use polled I/O to write a character to the console serial line
 *------------------------------------------------------------------------
 */
syscall kputc(
	  byte	c			/* character to write		*/
	)
{
	intmask mask;
	// STM32 specific: volatile struct uart_csreg * uptr = 0x40013800;

//RAFA	mask = disable();

	if (c == '\n')
		serial_put_char('\r');
	serial_put_char(c);
/*
	if (c == '\n') {
              while(!(uptr->sr & UART_TC));
	      uptr->dr = 0x0D; // return line
      	}
              while(!(uptr->sr & UART_TC));
	      uptr->dr = c;
*/

//RAFA	restore(mask);
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

	// RAFA
	char output[81];
	char *c;

	memset(output, 0, 81);
    va_start(ap, fmt);
     // RAFA _doprnt(fmt, ap, (int (*)(int))kputc);
    // vsnprintf(output, 80, fmt, ap);
    vsnprintf(output, 80, fmt, ap);
    va_end(ap);



	c = output;
	while(*c) {
		kputc(*c);
		c++;
	};
    return OK;
}
