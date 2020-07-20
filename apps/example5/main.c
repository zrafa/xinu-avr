/* ex5.c - main, prod2, cons2 */

#include <xinu.h>

void	prod2(sid32, sid32), cons2(sid32, sid32);

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
	resume( create(cons2, 1024, 20, "cons", 2, consumed, produced) );
	resume( create(prod2, 1024, 20, "prod", 2, consumed, produced) );
}

/*------------------------------------------------------------------------
 * prod2  --  increment n 2000 times, waiting for it to be consumed
 *------------------------------------------------------------------------
 */
void	prod2(
	  sid32		consumed,
	  sid32		produced
	)
{
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
void	cons2(
	  sid32		consumed,
	  sid32		produced
	)
{
	int32	i;

	for( i=1 ; i<=2000 ; i++ ) {
		wait(produced);
		printf("n is %d \n", n);
		signal(consumed);
	}
}
