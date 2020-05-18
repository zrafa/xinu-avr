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

/* Nested interrupt vector */
#define NVIC_ISER0	(uint32 *) 0xE000E100
#define	NVIC_ISER1	(uint32 *) 0xE000E104
#define NVIC_STIR	(uint32 *) 0xE000EF00

/* System control block */
#define SCB_ICSR	(uint32 *) 0xE000ED04
#define PENDSV_INTR	28

// #define MAXADDR		0x20010000		/* 64kB SRAM */
#define MAXADDR		0x20004E20		/* 64kB SRAM */ // RAFA
// #define MAXADDR		0x20004000		/* 64kB SRAM */ // RAFA
#define HANDLERSTACK	1024			/* Size reserved for stack in Handler mode */
