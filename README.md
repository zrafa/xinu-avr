## What is Xinu?
Xinu stands for Xinu Is Not Unix -- although it shares concepts and even names with Unix, the internal design differs completely. Xinu is a small, elegant operating system that supports dynamic process creation, dynamic memory allocation, network communication, local and remote file systems, a shell, and device-independent I/O functions. The small size makes Xinu suitable for embedded environments.

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

