#include <xinu.h>

#include <avr/interrupt.h>

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
// char cadena[100];

#define F_CPU 16000000UL

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define INIT 0x06
#define EN_RX_TX 0x18
#define UART_RXCIE0 7 

#define EN_TX 0x20
#define EN_RX 0x80



volatile uart_t *puerto_serial = (uart_t *) (0xc0);

void serial_init() {

	/* Configurar los registros High y Low con BAUD_PRESCALE */

	blink_avr();


	puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_c = (unsigned char)(INIT);

	/* Activar la recepcion y transmicion e interrupcion de recepcion */
	puerto_serial->status_control_b = (unsigned char)(EN_RX_TX | UART_RXCIE0);

	/* test */
	while(!((puerto_serial->status_control_a) & (EN_TX)));
	puerto_serial->data_es = 'R';
}


void serial_put_char (char outputChar)
{

	while(!((puerto_serial->status_control_a) & (EN_TX)));

	puerto_serial->data_es = outputChar;
}

char value;

/*
 * RX interrupt service rutine
 */
ISR(USART_RX_vect){
	cli(); 
	value = UDR0;             //read UART register into value
	ttyhandler (1, value, 0);
	sei(); 
}

char serial_get_char(void)
{
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

