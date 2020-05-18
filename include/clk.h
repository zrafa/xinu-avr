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

#define CLOCK_BASE 0x40021000;

/* Enable and check clock */
#define PLL_ENABLE 	24	
#define PLL2_ENABLE 	26
#define PLL3_ENABLE	28
#define HSE_ENABLE 	16
#define HSI_ENABLE 	1
#define HSE_READY	17

/* System clock switch */
#define HSI_SYSTEMCLOCK	0
#define HSE_SYSTEMCLOCK	1
#define PLL_SYSTEMCLOCK	2

#define SWITCH_READY	3

/* PLL setting */
#define PPLx4		0x00080000
#define PPLx5		0x000C0000
#define PPLx6		0x00100000
#define PPLx7		0x00140000
#define PPLx8		0x00180000
#define PPLx9		0x001C0000

#define HSE_PLL_SOURCE 	16
#define HSE_DIVIDERPLL	17

/* Enable Clock Signals APB2 */
#define IOPAEN		2
#define IOPBEN		3
#define IOPCEN		4
#define IOPDEN		5
#define IOPEEN		6
#define IOPFEN		7
#define	IOPGEN		8
#define ADC1EN		9
#define ADC2EN		10
#define TIM1EN		11
#define SPI1EN		12
#define TIM8EN		13
#define USART1EN	14

/* Enable Clock Signals APB1 */
#define TIM2EN		0
#define	TIM3EN		1
#define	TIM4EN		2
#define	TIM5EN		3
#define	TIM6EN		4

//int clockinit(struct dentry * devptr);
//int clockcontrol(struct dentry * devptr, int32_t func, int32_t, int32_t);

struct clock_csreg {
	volatile uint32 cr;
	volatile uint32 cfgr;
	volatile uint32 cir;
	volatile uint32 apb2rstr;
	volatile uint32 apb1rstr;
	volatile uint32 ahbenr;
	volatile uint32 apb2enr;
	volatile uint32 apb1enr;
	volatile uint32 bdcr;
	volatile uint32 csr;
	volatile uint32 ahbstr;
	volatile uint32 cfgr2;
};

