#include <xinu.h>

/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
// volatile uart_t *puerto_serial = (uart_t *) (0xc0);

char letra_start = 'R';
char cadena[100];

#define F_CPU 16000000UL

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define INIT 0x06
#define EN_RX_TX 0x18
#define EN_TX 0x20
#define EN_RX 0x80



void serial_init() {

	/* Configurar los registros High y Low con BAUD_PRESCALE */

	blink_avr();

       /* Load .data segment into SRAM */
        // extern uint32 * etext, data, edata;
	// extern uint32 * _rom_data_begin;
        // int size = (&edata - &data); 
        // memcpy(&data, &_rom_data_begin, size);    



  extern uint32_t __data;
  extern uint32_t __data_end;
  extern uint32_t __data_load;
  extern uint32_t __bss;
  extern uint32_t __bss_end;
  extern uint32_t __vectors;

  uint32_t *from = &__data_load;
  uint32_t *to = &__data;
  unsigned char b;
  // Relocate .data section
//  for (uint32_t *from = &__data_load, *to = &__data; to < &__data_end; from++, to++) {
 //   b = *from;
  //  *to = b;
  //}

  // Clear .bss
  //for (uint32_t *to = &__bss; to < &__bss_end; to++)
  //{
   // *to = 0;
  //}


	volatile uart_t *puerto_serial = (uart_t *) (0xc0);

	puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_c = (unsigned char)(INIT);

	/* Activar la recepcion y transmicion */
	puerto_serial->status_control_b = (unsigned char)(EN_RX_TX);

	while(!((puerto_serial->status_control_a) & (EN_TX)));
	// puerto_serial->data_es = letra_start;
	puerto_serial->data_es = 'R';
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
	volatile uart_t *puerto_serial = (uart_t *) (0xc0);

	while(!((puerto_serial->status_control_a) & (EN_TX)));

	puerto_serial->data_es = outputChar;
}


char serial_get_char(void)
{
	volatile uart_t *puerto_serial = (uart_t *) (0xc0);
    /* Wait for the next character to arrive. */
	while(!((puerto_serial->status_control_a) & (EN_RX)));
	return (puerto_serial->data_es);
}

void serial_put_str (char * mensaje)
{
	while (*mensaje) {
		serial_put_char(*mensaje);
		mensaje++;
	};
}

char* serial_get_str(void)
{
	int i = 0;
	char l = serial_get_char();
    	while((l != '\r') && (l != '\n') && (l != '\0')){
		cadena[i]=l;
		i++;
		l = serial_get_char();
	};
	cadena[i]='\0';/*agrega el fin de cadena*/
	return cadena;

}
