/* xinu.h - include all system header files */

// RAFA
extern void notmain(void);
typedef unsigned int size_t;
void blink_avr();
#include <messages.h>

// FIN DE RAFA


#include <kernel.h>
#include <cortexm3.h> 	/* Cortex M3 Processor */
#include <conf.h>
#include <process.h>
#include <queue.h>
#include <resched.h>
#include <semaphore.h>
#include <memory.h>
#include <bufpool.h>
#include <mark.h>
#include <ports.h>
#include <clk.h> 	/* STM32 Clock system */
#include <timer.h>	/* STM32 Timer peripheral */
#include <uart.h>	/* STM32 UART peripheral */
#include <tty.h>
#include <gpio.h>	/* STM32 GPIO peripherals */
#include <gpioselect.h>
#include <device.h>
#include <interrupt.h>
#include <file.h>
#include <rfilesys.h>
#include <rdisksys.h>
#include <lfilesys.h>
#include <spi.h>
#include <ether.h>
#include <net.h>
#include <ip.h>
#include <arp.h>
#include <udp.h>
#include <dhcp.h>
#include <icmp.h>
#include <tftp.h>
#include <name.h>
#include <shell.h>
#include <date.h>
#include <prototypes.h>
#include <delay.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>
