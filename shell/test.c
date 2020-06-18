/* xsh_test.c - xsh_test */

#include <xinu.h>
#include <stdio.h>

/* 
void sndA(void);
void sndB(void);
*/
// void prod2(sid32 consumed, sid32 produced, int a);
// void cons2(sid32 consumed, sid32 produced, int a);

int32 n = 0;
int32 j = 0;

//void cons2(sid32 consumed, sid32 produced, int a);
void cons2(int argc, char * argv[]);
void prod2(int argc, char * argv[]);

void freem(void)
{
	int mask = disable();
	uint32 free_mem=0;
	struct	memblk	*memptr;
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("\n\rFreeMEM:%d\n", free_mem);
	restore(mask);
}

/*------------------------------------------------------------------------
 * xhs_test
 *------------------------------------------------------------------------
 */
process test(int nargs, char *args[])
{
//	int32 a = roundmb(81);

	char buf[6];
	char buf2[6];
	memset(buf, 0, 6);
	memset(buf2, 0, 6);
	buf[0] = 49;
	buf[1] = 50;
	printf("b=%s\n", buf);
	write(EEPROM0, buf, 4);
	buf[0] = 0;
	buf[1] = 0;
	read(EEPROM0, buf2, 4);
	buf2[1] = 0;
	printf("b=%s\n", buf2);
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
/*
	sid32 produced, consumed;
	consumed = semcreate(0);
	produced = semcreate(1);
	printf ("prod=%d \n", produced);
	printf ("consu=%d \n", consumed);
	blink_avr();
	blink_avr();
	resume(create(cons2, 256, 20, "cons", 3, consumed, produced, 4));
	resume(create(prod2, 256, 20, "prod", 3, consumed, produced, 4));
*/
	return 0;
}

void prod2(int argc, char * argv[])
{
	sid32 consumed, produced;
	consumed = argv[0];
	produced = argv[1];
	int a = argv[2];
	int32 i;

		printf("argc=%d\n", argc);
		printf("n1=%d\n", consumed);
		printf("n2=%d\n", produced);
		printf("n3=%d\n", a);
	//for (i=1; i<=2000; i++) {
	for (i=1; i<=100; i++) {
//		printf("n3=%d\n", a);
		wait(consumed);
		j = j + 1;
		//n++;
		signal(produced);
	}
}

void cons2(int argc, char * argv[])
//void cons2(sid32 consumed, sid32 produced, int a)
{
	int32 i;

	sid32 consumed, produced;
	consumed = argv[0];
	produced = argv[1];
	//for (i=1; i<=2000; i++) {
	for (i=1; i<=100; i++) {
		wait(produced);
		n = n + (j*2);
		printf("n is %d \n", n);
		signal(consumed);
	}

}
/* original test 
process test(int nargs, char *args[])
{
	resume(create(sndA, 64, 20, "proc1", 0));
	resume(create(sndB, 64, 20, "proc1", 0));

	return 0;
}

void sndA(void)
{
	while(1)
		putc(CONSOLE, 'A');
}

void sndB(void)
{
	while(1)
		putc(CONSOLE, 'B');

}
end of original test */
