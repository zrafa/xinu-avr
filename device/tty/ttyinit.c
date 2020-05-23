/* ttyinit.c - ttyinit */

#include <xinu.h>

struct	ttycblk	ttytab[Ntty];

/*------------------------------------------------------------------------
 *  ttyinit  -  Initialize buffers and modes for a tty line
 *------------------------------------------------------------------------
 */
devcall	ttyinit(
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	struct	ttycblk	*typtr;		/* Pointer to ttytab entry	*/
	struct	uart_csreg *uptr;	/* Address of UART's CSRs	*/

	typtr = &ttytab[ devptr->dvminor ];

	/* Initialize values in the tty control block */

	typtr->tyihead = typtr->tyitail = 	/* Set up input queue	*/
		&typtr->tyibuff[0];		/*    as empty		*/
	typtr->tyisem = semcreate(0);		/* Input semaphore	*/
	typtr->tyohead = typtr->tyotail = 	/* Set up output queue	*/
		&typtr->tyobuff[0];		/*    as empty		*/
	typtr->tyosem = semcreate(TY_OBUFLEN);	/* Output semaphore	*/
	typtr->tyehead = typtr->tyetail = 	/* Set up echo queue	*/
		&typtr->tyebuff[0];		/*    as empty		*/
	typtr->tyimode = TY_IMCOOKED;		/* Start in cooked mode	*/
	typtr->tyiecho = TRUE;			/* Echo console input	*/
	typtr->tyieback = TRUE;			/* Honor erasing bksp	*/
	typtr->tyevis = TRUE;			/* Visual control chars	*/
	typtr->tyecrlf = TRUE;			/* Echo CRLF for NEWLINE*/
	typtr->tyicrlf = TRUE;			/* Map CR to NEWLINE	*/
	typtr->tyierase = TRUE;			/* Do erasing backspace	*/
	typtr->tyierasec = TY_BACKSP;		/* Primary erase char	*/
	typtr->tyierasec2= TY_BACKSP2;		/* Alternate erase char	*/
	typtr->tyeof = TRUE;			/* Honor eof on input	*/
	typtr->tyeofch = TY_EOFCH;		/* End-of-file character*/
	typtr->tyikill = TRUE;			/* Allow line kill	*/
	typtr->tyikillc = TY_KILLCH;		/* Set line kill to ^U	*/
	typtr->tyicursor = 0;			/* Start of input line	*/
	typtr->tyoflow = TRUE;			/* Handle flow control	*/
	typtr->tyoheld = FALSE;			/* Output not held	*/
	typtr->tyostop = TY_STOPCH;		/* Stop char is ^S	*/
	typtr->tyostart = TY_STRTCH;		/* Start char is ^Q	*/
	typtr->tyocrlf = TRUE;			/* Send CRLF for NEWLINE*/
	typtr->tyifullc = TY_FULLCH;		/* Send ^G when buffer	*/
						/*   is full		*/

	/* Initialize UART */
	// STM32 specifi: struct 	gpio_csreg *gptr;	
	// STM32 specifi: struct 	clock_csreg *cptr;

	/* Enable 'clock' on peripherals */
	// STM32 specifi: cptr = (struct clock_csreg *)CLOCK_BASE;
	// STM32 specifi: cptr->apb2enr |= (1 << IOPAEN) | (1 << USART1EN);

	/* Set in and output mode */
	// STM32 specifi: gptr = (struct gpio_csreg *)(0x40010800);
	// STM32 specifi: gptr->crh = 0x44444894;

	/* Enable peripheral */
	// STM32 specifi: uptr = (struct uart_csreg *)(0x40013800);
	// STM32 specifi: uptr->cr1 &= ~(1 << UART_EN);
	
	/* Set baudrate 115200 */
	// STM32 specifi: uptr->brr = 0x00000045;
	
	// STM32 specifi: uptr->cr1 |= (1 << UART_TX_EN) | (1 << UART_RX_EN); /* Enable lines */
	// STM32 specifi: uptr->cr1 |= (1 << UART_INTR_RX) | (1 << UART_INTR_TX); /* Enable interrupts */ 

	/* Set and enable interrupt vector */
	// STM32 specifi: set_evec(devptr->dvirq, (uint32)devptr->dvintr);
	// STM32 specifi: *NVIC_ISER1 |= (1 << 5);

	/* Start the device */
	// STM32 specifi: uptr->cr1 |= (1 << UART_EN);

//	ttykickout(uptr);
	return OK;
}
