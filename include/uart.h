/* Xinu for STM32
 *
 * Original license applies
 * Modifications for STM32 by Robin Krens
 * Please see LICENSE and AUTHORS 
 * 
 * $LOG$
 * 2019/11/11 - ROBIN KRENS
 * Initial version 
 * 
 * $DESCRIPTION$
 *
 * */

/* Control register */
#define UART_EN		13 
#define UART_INTR_RX	5
#define UART_INTR_TCIE	6
#define UART_INTR_TX	7
#define UART_TX_EN 	3
#define UART_RX_EN 	2

#define PARITY		12

/* Status register */
#define UART_RXNE	0x20
#define UART_TC		0x40
#define UART_TC_TXE	0xC0

#define UART_TEST	6

#define UART_FIFO_SIZE	1
#define UARTBUF 256
#define ECHO 1

struct uart_csreg {
	volatile uint32 sr;
	volatile uint32 dr;
	volatile uint32 brr;
	volatile uint32 cr1;
	volatile uint32 cr2;
	volatile uint32 cr3;
	volatile uint32 gtr;
};

