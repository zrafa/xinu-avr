#include <xinu.h>

int32	spiinit (
		 struct	dentry *devptr
		)
{
	struct spi_csreg *spiptr;	/* SPI control and status regs	*/
	struct clock_csreg *cptr; 

	//kprintf("INIT SPI!\n");

	/* Enable SPI clock */
	cptr = (struct clock_csreg *)CLOCK_BASE;
	cptr->apb2enr |= (1 << SPI1EN);
	
	/* Configure SPI peripheral */
	if(devptr->dvminor == 0) {
		spiptr = (struct spi_csreg *)SPI1_BASE;
	}
	else {
		kprintf("SPI device not recognized\n");
		return SYSERR;
	}

	spiptr->cr1 &= ~(1 << SPI_ENABLE); // temporarily disable device
	spiptr->cr1 |= (1 << SPI_MSTR) | (1 << SPI_SSM) | (1 << SPI_SSI) |
		(1 << SPI_BIDIMODE) | (1 << SPI_BIDIOE);

	/* Set Baud rate */
	spiptr->cr1 |= BR_FPCLKDIV8;

	/* Enable SPI peripheral */
	spiptr->cr1 |= (1 << SPI_ENABLE);

	return OK;
}
