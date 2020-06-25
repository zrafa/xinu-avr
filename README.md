# Xinu OS for AVR atmega328p (Arduino)

## What is Xinu?

Xinu is a small, elegant, and easy to understand operating system,
originally developed by Douglas Comer for instructional purposes at
Purdue University in the 1980s.

The Operating System Xinu supports dynamic process creation, dynamic memory allocation, network communication, local and remote file systems, a shell, and device-independent I/O functions. 

Since the whole source code size is small, Xinu is suitable 
for embedded systems.  Xinu uses  powerful  
primitives to provide the same functionality many conventional 
operating systems supply (despite its small size).

Many sites defines Xinu as a free Unix system, or similar statements.
It is not. Xinu differs completely
from the internal structure of Unix (or Linux). 
For academic purposes Xinu is smaller, elegant, and easier to understand.
Applications written for one system will not
run on the other without modification. **Xinu is not Unix.**

### History

Xinu originally ran on  Digital  Equipment  Corporation
LSI  11's with only 64K bytes of memory, at the end of 1979 
and the inning of 1980. Over the years Xinu versions 
Xinu have been expanded and ported to a wide variety of architectures and platforms, including: IBM PC, 
Macintosh, Digital Equipment Corporation VAX and DECStation 3100, Sun Microsystems Sun 2, 
Sun 3 and Sparcstations, and for several ARM, MIPS and x86 embedded boards.
It has been used as the basis for many research projects. 
Furthermore, Xinu has been used as an embedded system in products 
by companies such as Motorola, Mitsubishi, Hewlett-Packard, and Lexmark. 
There is a full TCP/IP stack, and even the original version of Xinu 
(for the PDP-11) supported arbitrary processes and network I/O.

There are current versions of Xinu for Galileo Intel boards,
ARM Beagle Boards, several MIPS platforms, and for x86 PC hardware 
and virtual machines.

## Xinu OS for AVR atmega328p

This version of Xinu runs on AVR atmega328 microcontrollers,
(still if those MCUs have 2KB of SRAM, 32KB of Flash memory and 1KB of EEPROM.
This port of Xinu uses 17KB of FLASH and 0.9KB of RAM, so there
are still resources (SRAM and FLASH) available for developing 
an embedded system solution programming 
concurrent processes under a real operating system; using for example,
an Arduino hardware and the Xinu operating system inside.

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


