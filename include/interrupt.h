/* interrupt.h */

struct scb_csreg {
	volatile uint32 cpuid;  
	volatile uint32 icsr;  
	volatile uint32 vtor;  
	volatile uint32 aircr;  
	volatile uint32 scr;  
	volatile uint32 ccr;  
	volatile uint32 shpr1;  
	volatile uint32 shpr2;  
	volatile uint32 shpr3;  
	volatile uint32 shcsr;  
	volatile uint32 cfcsr;  
	volatile uint32 hfsr;  
	volatile uint32 mmar;  
	volatile uint32 bfar;  
};

/* System control block base */
#define SCB_BASE	0xE000ED00

/* Faults enable */
#define	MPUFAULT_EN	16
#define	BUSFAULT_EN	17
#define USAGEFAULT_EN	18

/* Exception vector */
#define MEMFAULT_ENTRY		4
#define BUSFAULT_ENTRY		5
#define USAGEFAULT_ENTRY	6
#define SVC_ENTRY		11
#define PENDSV_ENTRY		14
#define SYSTICK_ENTRY		15
