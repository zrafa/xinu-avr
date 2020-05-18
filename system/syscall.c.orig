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

#include <xinu.h>

/* System call handler 
 * The __attribute__((naked)) makes sure the compiler doesn't
 * places registers on the stack
 *
 * A SVC is similar to an exception or interrupt
 * A stack frame is pushed on entry and popped
 * on exit BY PROCESSOR. Please see in-function command */

__attribute__ ((naked))
void _svc_handler(void) {

	uint32 * args;

	/* Test whether system call was invoked from supervisor (use MSP) or
	 * user (use PSP) mode (needed for future purposes) */
	asm volatile (
	"tst lr, #4" "\n\t"
	"ite eq" "\n\t"
	"mrseq %0, msp" "\n\t"
	"mrsne %0, psp" "\n\t"
	"push {lr}" "\n\t"
	"push {r4-r11}" : "=r" (args));

	/* An exception (or interrupt) before entering this handler
	 * places the following on the stack 
	 * 
	 * R0 <- args[0]
	 * R1 <- args[1]
	 * R2 
	 * R3
	 * R12
	 * LR <- Not a real LR, A certain 'mask'
	 * PC <- placed at args[6], see description below
	 * PSR <- Status of processor before call
	 *
	 * PC contains the return address that will continue after this SVC handler
	 * is finised. The previous address (the svc # call) is at PC - 2, the
	 * first byte contains the svc number.
	 * */

	//uint8 svc_nr = ((char *) args[6])[-2];
	uint8 svc_nr = args[0];
	int ret = -1;
	struct procent * p;

	switch(svc_nr) {
		/* The nullprocess is a special case and used only for startup
		 * The stack for the nullprocess is loaded and the processor makes
		 * a jump back to thread mode with the PSP stack */
		case XINU_NULLPROCESS:
			p = (struct procent *) args[1]; 
	  		asm volatile ("mov r0, %0" : : "r" (p->prstkptr));
                	asm volatile("ldmia r0!, {r4-r11} ");
                 	asm volatile ("msr psp, r0");
                 	asm volatile (
                          "ldr r0, =0xFFFFFFFD" "\n\t"
                          "mov lr, r0" "\n\t"
                          "bx lr");
			break;
		case XINU_PUTC: /* Example system call usage */
			ret = putc(args[1], args[2]);
			break;
		default:
			kprintf("System call not implemented\n");	
			break;
	}

	/* Return value in r0 for callee */
	args[0] = ret;

	asm volatile ("pop {r4-r11}");
	/* exception return, 0xFFFFFFFX (<-- last value is flag
	 * and gives the processor information to return to what */
	asm volatile ("pop {lr}"); 
	asm volatile ("bx lr");


}

void syscall_init() {
	/* SVC handler function is set in the interrupt vector table  */
	set_evec(SVC_ENTRY, (uint32)_svc_handler);
}


