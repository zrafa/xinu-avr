/* ex5.c - main, prod2, cons2 */

#include <xinu.h>

void	prod2(int nargs, char *args[]);
void	cons2(int nargs, char *args[]);

int32	n = 0;			/* n assigned an initial value of zero	*/

/*------------------------------------------------------------------------
 *  main  --  producer and consumer processes synchronized with semaphores
 *------------------------------------------------------------------------
 */
void	main(void)
{
	sid32	produced, consumed;

	consumed = semcreate(0);
	produced = semcreate(1);
	resume( create(cons2, 256, 20, "cons", 2, consumed, produced) );
	resume( create(prod2, 256, 20, "prod", 2, consumed, produced) );
}

/*------------------------------------------------------------------------
 * prod2  --  increment n 2000 times, waiting for it to be consumed
 *------------------------------------------------------------------------
 */
void	prod2(int nargs, char *args[])
{
	sid32 consumed = args[0];
	sid32 produced = args[1];
	int32	i;

	for( i=1 ; i<=2000 ; i++ ) {
		wait(consumed);
		n++;
		signal(produced);
	}
}

/*------------------------------------------------------------------------
 * cons2  --  print n 2000 times, waiting for it to be produced
 *------------------------------------------------------------------------
 */
void	cons2(int nargs, char *args[])
{
	sid32 consumed = args[0];
	sid32 produced = args[1];
	int32	i;

	for( i=1 ; i<=2000 ; i++ ) {
		wait(produced);
		printf("n is %d \n", n);
		signal(consumed);
	}
}
