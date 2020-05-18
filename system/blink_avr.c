
#include <avr/io.h>

void my_delay(unsigned long delay) {
  volatile unsigned long i = 0;
  for (i = 0; i < delay; i++) {
      __asm__ __volatile__ ("nop");
  }
}


void blink_avr(void) {

	DDRB = (1<<PB5); //Pin B5 Salida

		PORTB |= (1<<PB5); //Ponemos el pin en alto
		my_delay(200000);
		PORTB &= ~(1<<PB5); //Ponemos el pin en bajo
		my_delay(200000);
}

