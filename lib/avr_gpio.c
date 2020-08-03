
/* avr_gpio.c - little lib to set/unset AVR digital out pins */

void gpio_write(char p, unsigned char v)
{
	volatile unsigned char * DDR;  /* port b _B = 0x24; DDR B address */
	volatile unsigned char * PORT;  /* port b = 0x25; PORT address */
	switch (p) {
	case 'b':
		DDR =  0x24;
		PORT = 0x25;
		break;
	default:
		return -1;
	}


	
	*(PORT) = 0x00;
	*(DDR) = 0xff;
	*(PORT) = v;
}

/* p : port. e.g. 'b' */
char gpio_read(char p)
{
	volatile unsigned char * DDR;  /* port b _B = 0x24; DDR B address */
	volatile unsigned char * PORT;  /* port b = 0x25; PORT address */
	char v;

	switch (p) {
	case 'b':
		DDR =  0x24;
		PORT = 0x25;
		break;
	default:
		return -1;
	}

	v = *(PORT);
	return v;


}

/* digital set high/low using arduino board pin number */
gpio_arduino_write(char pin, unsigned char v)
{
	char p;
	unsigned char val;


	/* Extra arduino mode */

	if (pin <= 8) {
		pin = (1 << pin); /* e.g. p = 3 (pin 3, port d) */
		p = 'd';
	} else if (pin <= 13) {
		pin = (1 << (pin-8)); /* e.g. p = 3 (pin 3, port d) */
		p = 'b';
	} else {
		pin = (1 << (pin-13)); /* e.g. p = 3 (pin 3, port d) */
		p = 'c';
	} 

	val = gpio_read(p);

	if (v)		/* 1 = high  ;  0 = low */
		v = val | pin;
	else 
		v = val & (~pin);

	gpio_write(p, v);
	return 0;
}

