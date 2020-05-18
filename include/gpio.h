/* gpio.h - definintions for the gpio device */

/*
 * Control and Status Register (CSR) definintions for the GPIO.
 * The code maps the structure structure directly onto the base address
 * CSR address for the device.
 */

/* Number of GPIO devices in the hardware */
#define NGPIO	4

/* REGISTER BASE */
#define GPIO1_BASE      (struct gpio_csreg *)0x40011400
#define GPIO2_BASE      (struct gpio_csreg *)0x40011000
#define GPIO3_BASE      (struct gpio_csreg *)0x40010C00
#define GPIO4_BASE      (struct gpio_csreg *)0x40010800

#define SETCFG		0
#define SETMODE		1

#define INPUT_MODE	0x0
#define OUTPUT_10MHZ	0x1
#define	OUTPUT_2MHZ	0x2
#define OUTPUT_50MHZ	0x3

#define MODE_ANALOG	0x0
#define	MODE_FLOATING	0x1
#define	MODE_INPUT	0x2

#define MODE_GENERAL_PUSHPULL	0x0
#define MODE_GENERAL_OPENDRAIN	0x1
#define MODE_ALT_PUSHPULL	0x2
#define MODE_ALT_OPENDRAIN	0x3

#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define PIN8	8
#define PIN9	9
#define PIN10	10
#define PIN11	11
#define PIN12	12
#define PIN13	13
#define PIN14	14
#define PIN15	15
#define PIN16	16

//int gpiowrite(struct dentry * devptr, void * value, uint32_t pinmask);
//int gpioinit(struct dentry * devptr);
//int gpiocontrol(struct dentry * devptr, uint32_t, uint32_t, uint32_t);

struct gpio_csreg {
	volatile uint32 crl;
	volatile uint32 crh;
	volatile uint32 idr;
	volatile uint32 odr;
	volatile uint32 bsrr;
	volatile uint32 brr;
	volatile uint32 lckr;
};


typedef void (*gpiointhook)(uint32, uint32);

struct	gpiocblk	{	/* GPIO control block			*/
	gpiointhook gphookfn;	/* Interrupt hook function		*/
};

extern	struct	gpiocblk	gpiotab[];

/* Pin Masks */
// #define PIN_MASK(pin)	 (1<<pin)
// #define GPIO_PIN_ALL     0xFFFFFFFF
// #define GPIO_PIN_00      0x00000001
// #define GPIO_PIN_01      0x00000002
// #define GPIO_PIN_02      0x00000004
// #define GPIO_PIN_03      0x00000008
// #define GPIO_PIN_04      0x00000010
// #define GPIO_PIN_05      0x00000020
// #define GPIO_PIN_06      0x00000040
// #define GPIO_PIN_07      0x00000080
// #define GPIO_PIN_08      0x00000100
// #define GPIO_PIN_09      0x00000200
// #define GPIO_PIN_10      0x00000400
// #define GPIO_PIN_11      0x00000800
// #define GPIO_PIN_12      0x00001000
// #define GPIO_PIN_13      0x00002000
// #define GPIO_PIN_14      0x00004000
// #define GPIO_PIN_15      0x00008000
// #define GPIO_PIN_16      0x00010000
// #define GPIO_PIN_17      0x00020000
// #define GPIO_PIN_18      0x00040000
// #define GPIO_PIN_19      0x00080000
// #define GPIO_PIN_20      0x00100000
// #define GPIO_PIN_21      0x00200000
// #define GPIO_PIN_22      0x00400000
// #define GPIO_PIN_23      0x00800000
// #define GPIO_PIN_24      0x01000000
// #define GPIO_PIN_25      0x02000000
// #define GPIO_PIN_26      0x04000000
// #define GPIO_PIN_27      0x08000000
// #define GPIO_PIN_28      0x10000000
// #define GPIO_PIN_29      0x20000000
// #define GPIO_PIN_30      0x40000000
// #define GPIO_PIN_31      0x80000000
// 
// /* Pin values */
// #define GPIO_VALUE_LOW		0x00
// #define GPIO_VALUE_HIGH		0x01
// 
// /* Control features */
// #define GPIO_OUTPUT_DISABLE    	0x00
// #define GPIO_OUTPUT_ENABLE    	0x01
// #define GPIO_REG_INT_HANDLER	0x02
// #define GPIO_INTERRUPT_CTL		0x03
// #define GPIO_DEB_SET_TIME		0x04
// #define GPIO_READ_PIN			0x05
// #define GPIO_WRITE_PIN			0x06
// 
// 
// /* Control Flags */
// #define GPIO_INT_LINE0_EN 	0x01
// #define GPIO_INT_LINE1_EN	0x02
// #define GPIO_INT_RISE_TRIG 	0x04
// #define GPIO_INT_FALL_TRIG	0x08
// #define GPIO_INT_LVL0_TRIG 	0x10
// #define GPIO_INT_LVL1_TRIG	0x20
// #define GPIO_INT_ALL_LINES 	(GPIO_INT_LINE0_EN|GPIO_INT_LINE1_EN)
// #define GPIO_INT_ALL_TRIG	(GPIO_INT_RISE_TRIG|GPIO_INT_FALL_TRIG|GPIO_INT_LVL0_TRIG|GPIO_INT_LVL1_TRIG)
// 
// 
// 
// /* Interrupt vector assignments */
// 
// #define GPIO0_INT_A		96
// #define GPIO0_INT_B		97
// #define GPIO1_INT_A		98
// #define GPIO1_INT_B		99
// #define GPIO2_INT_A		32
// #define GPIO2_INT_B		33
// #define GPIO3_INT_A		62
// #define GPIO3_INT_B		63
// 
// /* PRCM Register addresses used for debounce clock */
// 
// #define PRCM_FCLK_GPIO1	(uint32 *)0x44E000AC
// #define PRCM_FCLK_GPIO2	(uint32 *)0x44E000B0
// #define PRCM_FCLK_GPIO3	(uint32 *)0x44E000B4
// #define PRCM_FCLK_BIT	(0x1<<18)
