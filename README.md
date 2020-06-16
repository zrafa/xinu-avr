# AVR atmega328p (Arduino) Xinu OS

## What is Xinu?

Xinu stands for Xinu Is Not Unix -- 

Xinu [1][2] is a small, elegant operating system.

Xinu supports dynamic process creation, dynamic memory allocation, network communication, local and remote file systems, a shell, and device-independent I/O functions. The small size makes Xinu suitable for embedded environments.

Xinu arranges  the  components  of  the system into a hiearchy of
layers, clarifying the interaction between the various  com-
ponents of the system and making the system easier to under-
stand and modify.  Despite its small size, Xinu uses  power-
ful  primitives  to provide the same functionality many con-
ventional operating systems supply.

As we will see, the internal structure of Xinu differs completely
from the internal structure of Unix (or Linux). 
Xinu is smaller, elegant, and easier to understand.
Applications written for one system will not
run on the other without modification. Xinu is not Unix.

Xinu originally ran on  Digital  Equipment  Corporation
LSI  11's with only 64K bytes of memory, at the end of 1979 
and the inning of 1980.
Over the years Xinu versions have  been  ported
to  many  architectures  including  the IBM PC (x86), Sun 3, 
Transputer, MacIntosh, x86, ARM, and MIPS. There 
are current versions of Xinu for Galileo Intel boards,
Beagle Boards, several MIPS platforms, and for PC hardware.
Also, for virtual machines.

This version of Xinu runs on AVR atmega328 microcontroller,
so it is possible to build an embedded system solution using the
Arduino hardware and the Xinu operating system inside.


Version 6 Xinu, as
it was called, supplied primitives to handle memory  manage-
ment,          process          management,          process
coordination/synchronization,  interprocess   communication,
real-time clock management, device drivers, and intermachine
communication (a ring network).  Version 7 Xinu replaced the


## What is Xinu for STM32
Xinu for STM32 is a port of the ARM version of Xinu. The STM32 family of 32-bit microcontrollers is a popular SoC based on the Arm Cortex-M processor.
Besides porting the original version, Xinu for STM32 is extended with the following specific Cortex-M* features:

* Shadowed Stack Pointer:  Two stack pointers are available. The MSP is used
for the OS Kernel and interrupt handlers. The PSP is used by application
tasks.
* PendSV exception for scheduling: If Xinu decides that context switching is needed,
it sets the pending status of the PendSV, and delays the context-switching
request until all other IRQ handlers have completed their processing before 
carrying out the PendSV exception 

## Supported Peripherals (currently)
* UART (Serial)
* GPIO
* SPI

## Tested boards
1. STM32F103* - https://stm32-base.org/boards/STM32F103RCT6-STM32-Mini-V2.0
2. Qemu for STM32 - https://github.com/beckus/qemu_stm32

## How to build and run
Xinu for STM32 uses simple Makefiles. The source code should be compiled with a cross compiler (i.e. Ubuntu's standard package: GCC cross compiler for ARM Cortex-A/R/M processors)
STM32Flash (https://sourceforge.net/projects/stm32flash) can be used for flashing the compiled code to the device's flash ROM. Use `qemu make` to run Xinu for STM32 in Qemu. Please note that this version of qemu should be manually build (see https://github.com/beckus/qemu_stm32)


## Screenshots
![Screenshot](https://github.com/robinkrens/xinu-for-stm32/raw/master/screenshot.png "bootscreen")

More general information about Xinu can be found at https://xinu.cs.purdue.edu/

