/* spi.h - SPI definitions */

/* avr : this port does not use spi yet */
/* values below for another platform-arch */

struct	spi_csreg {
	volatile uint32 cr1;		
	volatile uint32 cr2;		
	volatile uint32 sr;	
	volatile uint32 dr;
	volatile uint32 crcpr;		
	volatile uint32 rxcrcr;
	volatile uint32 txcrcr;		
	volatile uint32 i2scfgr;
	volatile uint32 i2spr;	
};

/* No SPI0 peripheral, starts from 1*/
#define	SPI1_BASE	0x40013000

/* Control register settings */
#define SPI_MSTR	2
#define SPI_ENABLE	6
#define SPI_SSM		9
#define	SPI_SSI		8
#define	SPI_BIDIMODE	15
#define SPI_BIDIOE	14

/* Status register flags */
#define SPI_BSY		7 // Busy
#define SPI_TXE		1 // Transfer buffer empty
#define SPI_RXNE	2 // Receive buffer NOT empty

/* Baud rate control */
#define BR_FPCLKDIV2	0x00000000
#define BR_FPCLKDIV4	0x00000008
#define	BR_FPCLKDIV8	0x00000010
#define BR_FPCLKDIV16	0x00000018
#define	BR_FPCLKDIV32	0x00000020
#define BR_FPCLKDIV64	0x00000028
