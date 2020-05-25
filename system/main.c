/*  main.c  - main */
// This is user land

#include <xinu.h>
#include <avr/interrupt.h>

extern void notmain(void);

process	main2(void)
{
	serial_put_char('2');
	serial_put_char('2');
}

process	main(void)
{
	//RAFA
	// notmain();

	/* Run the Xinu shell */
	// recvclr();

	
	kprintf("MAIN\n");
	//blink_avr();
	//blink_avr();
	//blink_avr();
	//blink_avr();
	blink_avr();
	blink_avr();
	// RAFA resume(create(shell, 4096, 50, "shell", 1, 0));
	// resume(create(shell, 64, 50, "shell", 1, 0));
	// resume(create(shell, 64, 50, "shell", 0, NULL));
	resume(create((void *)main2, INITSTK, 50, "main2", 0, NULL));

	
	for(;;)
	serial_put_char('4');
	/* Wait for shell to exit and recreate it */

	kprintf("EXIT SHELL\n");
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
