#include <xinu.h>

__attribute__((naked))
uint32 xinu_syscall(int nr, uint32 arg1, uint32 arg2, uint32 arg3) 
{
/*
	asm volatile("push {r0-r11}");
	asm volatile("push {lr}");
	asm volatile("svc 1"); /* Hack: For all service call use 1, arg1 got number */
/*
	asm volatile("pop {lr}");
	asm volatile("pop {r0-r11}");
	asm volatile("bx lr");
*/

}	



//void xinu_open(did32 descrp, char * name, char * mode) {
//		
//		xinu_syscall(XINU_OPEN, descrp, name, mode);			
//}

int xinu_uptime() {

	return xinu_syscall(XINU_UPTIME, 0, 0, 0);
}

int xinu_putc(int dev, char c) {

	return xinu_syscall(XINU_PUTC, dev, c, 0 );
	//return xinu_syscall(XINU_PUTC, dev, c, 0);
}


//int xinu_close(dev);
//int xinu_putc(dev);
//
//int xinu_yield();
//int xinu_receive();
//
//int xinu_gettime();
