/* evec.c -- initintc, set_evec	*/

typedef unsigned int size_t;
#include <avr/pgmspace.h>

#include <xinu.h>
#include <stdio.h>


// RAFA uint32	__attribute__((aligned(0x100))) intc_vector[92];	/* Interrupt vector	*/

/* Each message corresponds to an exception in the vector table. */
char * exception_message(uint8 intnr) {


/* RAFA 
E_A    "--",
E_B    "RESET",
E_etc    "NMI",
    "HARD FAULT",
    "MEMMANAGE FAULT",
    "BUS FAULT",
    "USAGE FAULT",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "SVC",
    "DEBUG MONITOR",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "PENDSV",
    "SYSTICK",
    "IRQ1",
    "IRQ2",
    "IRQ3",
    "IRQ4",
    // add more if needed
*/
// RAFA char * messages[] = {
const char messages[] PROGMEM = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'N',
    'N',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    // add more if needed
};

if (intnr < 20) // TODO: strlen
	return pgm_read_word(&messages[intnr]);

return "UNKNOWN";

}

__attribute__ ((naked)) void * dummy_isr(void) {

	uint32 * current_sp;

	/* Test whether system call was invoked from supervisor (use MSP) or
	 * user (use PSP) mode */
	/*	asm volatile (
	"tst lr, #4" "\n\t"
	"ite eq" "\n\t"
	"mrseq %0, msp" "\n\t"
	"mrsne %0, psp" : "=r" (current_sp)); */

/*
	asm volatile ("mrs %0, psp" : "=r" (current_sp));

      	uint8 nr = *SCB_ICSR & 0xFF;
      	kprintf("EXCEPTION: %s\n", exception_message(nr));
	kprintf("STACKFRAME:\n");
	for (int i = 0; i < 8; i++) {
		kprintf("STACK[%d]: %x\n", i, current_sp[i]);
	}
	
	halt(); 
*/
}
/*------------------------------------------------------------------------
 * initintc - Initialize the Interrupt Controller
 *------------------------------------------------------------------------
 */
int32	initintc()
{
	/* System control block */
	// STM32 specific: struct	scb_csreg *csrptr = (struct scb_csreg *)0xE000ED00;
	
	/* clear entire IVT location in memory  */
	// RAFA memset(&intc_vector, 0, (sizeof(uint32) * 92));

	/* set dummy handlers */
	for (int i = 1; i <= 64 ; i++) {
		set_evec(i, (uint32) dummy_isr);
	}

	/* Enable memory management, bus and usage fault exceptions handlers
	 * If these are not enabled, the processor treats them as a hard
	 * faults. Unpriviliged access will cause a busfault in case no MPU */
	// STM32 specific: srptr->shcsr |= (1 << MPUFAULT_EN) | (1 << BUSFAULT_EN) | (1 << USAGEFAULT_EN);	
	
	/* The vector table is intially at 0x0. The vector table can be
	 * relocated to other memory locations. We can do this by setting 
	 * a register in the NVIC called the vector table offset register */
	// RAFA // STM32 specific: srptr->vtor = (uint32) &intc_vector;
	
	return OK;
}

/*------------------------------------------------------------------------
 * set_evec - set exception vector to point to an exception handler
 *------------------------------------------------------------------------
 */
int32	set_evec(uint32 xnum, uint32 handler)
{
	/* There are only 92 interrupts allowed 0-2 */

	if(xnum > 92) {
		return SYSERR;
	}

	/* Install the handler */

	// STM32 specific: intc_vector[xnum] = handler;

	return OK;
}

