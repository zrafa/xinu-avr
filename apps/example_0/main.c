/*  main.c  - main */

#include <xinu.h>

process	main(void)
{

	/* Run the Xinu shell */

//RAFA	recvclr();
//RAFA	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

//RAFA	while (TRUE) {
//RAFA		receive();
//RAFA		sleepms(200);
//RAFA		kprintf("\n\nMain process recreating shell\n\n");
//RAFA		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
//RAFA	}
	return OK;
    
}
