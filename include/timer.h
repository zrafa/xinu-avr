/* STM32 Timer
General purpose timer */

extern	uint32	clktime;	/* current time in secs since boot	*/
extern  uint32  count1000;      /* ms since last clock tick             */

extern	qid16	sleepq;		/* queue for sleeping processes		*/
extern	int32	slnonempty;	/* nonzero if sleepq is nonempty	*/
extern	int32	*sltop;		/* ptr to key in first item on sleepq	*/
extern	uint32	preempt;	/* preemption counter			*/

#define TIM2_BASE	0x40000000
#define	TIM2_IRQ	44

#define TIM_CEN		0
#define	TIM_UDIS 	1
#define TIM_URS		2

#define	TIM_UDE		8
#define TIM_UIE		7	/* */

#define TIM_UIF		0	/* Update interrupt flag*/

struct timer_csreg {
	volatile uint32 cr1;
	volatile uint32 cr2;
	volatile uint32 smcr;
	volatile uint32 dier;
	volatile uint32 sr;
	volatile uint32 egr;
	volatile uint32 ccmr1;
	volatile uint32 ccmr2;
	volatile uint32	ccer;
	volatile uint32 cnt;
	volatile uint32 psc;
	volatile uint32 arr;
};
