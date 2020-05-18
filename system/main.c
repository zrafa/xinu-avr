/*  main.c  - main */
// This is user land

#include <xinu.h>

extern void notmain(void);

process	main(void)
{
	//RAFA
	notmain();

	/* Run the Xinu shell */
	recvclr();

	
	resume(create(shell, 4096, 50, "shell", 1, 0));
	
	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		//kprintf("Entering sleep");
		sleepms(200);
		// RAFA kprintf("\n\nMain process recreating shell\n\n");
		kprintf(&m1[0]);
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
