#include <xinu.h>

void avr_printf(char mess[])
{
	char t[80];

	memset(t, 0, 80);
	strncpy_P(t, mess, 79);
	printf("%s", t);
}

// void avr_kprintf(char mess[])
void avr_kprintf(const unsigned char *msg)
{
//	char t[80];

       intmask mask;

       mask = disable();


  while( pgm_read_byte( msg ) != 0 ) {
//    printf( "%c", pgm_read_byte( msg++ ) );
    putchar(pgm_read_byte( msg++ ) );
  };


        restore(mask);
/*
	memset(t, 0, 80);
	strncpy_P(t, mess, 79);
	printf("%s", t);
*/
}
