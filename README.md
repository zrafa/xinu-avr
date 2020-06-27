# Xinu OS for AVR atmega328p (Arduino)

Xinu OS for AVR atmega328p (Arduino)
This repository keeps the source code of a Xinu operating system version targeted for the AVR atmega328p microcontroller. Most of Xinu kernel has been ported in this work in progress. For an interesting exercise the Xinu shell for user interface and several programs and UNIX-like utilities are provided as well.

Current Xinu versions are designed for ARM, MIPS and x86 architectures . The hardware differences between those and the ultra small AVR microcontroller required substantial changes to some low-level structure of Xinu, mainly to use
the FLASH memory in the AVR MCU for several read only data structures previously
in RAM.



## What is Xinu?

Xinu is a small, elegant, and easy to understand operating system, originally developed by Douglas Comer for instructional purposes at Purdue University in the 1980s.

The Xinu Operating System includes: dynamic process creation, dynamic memory allocation, real-time clock management, process coordination and synchronization, local and remote file systems, a shell, and device-independent I/O functions.  

Xinu uses powerful primitives to provides all the componentes and the same functionality many conventional operating sytems supply. Since the whole source code size is small, Xinu is suitable for embedded systems.

Many sites defines Xinu as a free Unix system, or similar statements. It is not. Xinu differs completely from the internal structure of Unix (or Linux). For academic purposes Xinu is smaller, elegant, and easier to understand. Applications written for one system will not run on the other without modification. Xinu is not Unix.

## History

Xinu originally ran on Digital Equipment Corporation LSI 11's with only 64K bytes of memory, at the end of 1979 and the inning of 1980. Over the years Xinu versions Xinu have been expanded and ported to a wide variety of architectures and platforms, including: IBM PC, Macintosh, Digital Equipment Corporation VAX and DECStation 3100, Sun Microsystems Sun 2, Sun 3 and Sparcstations, and for several ARM, MIPS and x86 embedded boards. It has been used as the basis for many research projects. Furthermore, Xinu has been used as an embedded system in products by companies such as Motorola, Mitsubishi, Hewlett-Packard, and Lexmark. There is a full TCP/IP stack, and even the original version of Xinu (for the PDP-11) supported arbitrary processes and network I/O.

There are current versions of Xinu for Galileo Intel boards, ARM Beagle Boards, several MIPS platforms, and for x86 PC hardware and virtual machines.

## Xinu OS for AVR atmega328p

This MCU has just 2KB of SRAM, 32KB of Flash memory, and 1KB of EEPROM,
so the work in progress is stimulating and very fun for lovers
of embedded systems development and operating system internals.

This port of Xinu fits in 17KB of FLASH and 0.9KB of RAM, so there
are still room (SRAM and FLASH) available for developing 
an embedded system solution, programming 
concurrent processes under a real operating system. For example,
using an Arduino hardware board.

Xinu is easy of understand, so a developer can obtain a copy 
of the system to examine, modify,
instrument, measure, extend, or transport it to another architecture.

## Douglas Comer

Douglas Comer is a Professor of Computer Science at Purdue University who
was inducted into the Internet Hall of Fame on September, 2019.

https://www.cs.purdue.edu/homes/comer/
https://www.cs.purdue.edu/news/articles/2019/comer_ihof.html

As one of the earliest TCP/IP and internetworking researchers, Comer wrote the first series of textbooks explaining the scientific principles underlying the design of the Internet and its communications protocols, providing some of the earliest formal guidance for building efficient networks and applications that use the Internet. 

Comer’s three-volume textbook series, Internetworking with TCP/IP, written in 1987, is widely considered to be the authoritative reference for Internet protocols. The series played a key role in popularizing Internet protocols by making them more understandable to a new generation of engineers and IT professionals. 

Version 6 Xinu, as
it was called, supplied primitives to handle memory  manage-
ment,          process          management,          process
coordination/synchronization,  interprocess   communication,
real-time clock management, device drivers, and intermachine
communication (a ring network).  Version 7 Xinu replaced the


