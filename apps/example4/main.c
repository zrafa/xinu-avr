/* ex4.c - main, produce, consume */

#include <xinu.h>

void	produce(void), consume(void);

int32	n = 0;	      /* external variables are shared by all processes	*/

/*------------------------------------------------------------------------
 *  main  --  example of unsynchronized producer and consumer processes
 *------------------------------------------------------------------------
 */
void	main(void)
{
	resume( create(consume, 256, 20, "cons", 0) );
	resume( create(produce, 256, 20, "prod", 0) );
}

/*------------------------------------------------------------------------
 * produce  --  increment n 2000 times and exit
 *------------------------------------------------------------------------
 */
void	produce(void)
{
	int32	i;

	for( i=1 ; i<=2000 ; i++ )
		n++;
}

/*------------------------------------------------------------------------
 * consume  --  print n 2000 times and exit
 *------------------------------------------------------------------------
 */
void	consume(void)
{
	int32	i;

	for( i=1 ; i<=2000 ; i++ )
		printf("The value of n is %d \n", n);
}
