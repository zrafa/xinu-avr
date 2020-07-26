/* xinu.h - include all system header files */

/* avr specific */
#include <avr_messages.h>

#include <kernel.h>
#include <conf.h>
#include <process.h>
#include <queue.h>
#include <resched.h>
#include <semaphore.h>
#include <memory.h>
#include <bufpool.h>
#include <mark.h>
#include <ports.h>
#include <timer.h>
#include <uart.h>	/* avr UART peripheral */
#include <tty.h>
#include <gpio.h>	/* avr GPIO peripherals */
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
