
/* avr specific */

typedef unsigned int size_t;
#include <avr/pgmspace.h>

const __flash char sysinit_m0[] = "\nWelcome to Xinu!\n\n\r\tXinu OS Copyright (c) 2012, 2015\n\r\tDouglas E. Comer and CRC Press, Inc.\n\n\r\tXinu OS for AVR atmega328p v0.1 (c) 2020\n\r\tRafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>\n\n\r";
const __flash char m1[] = "\n\nRecreating shell\n\n";
const __flash char m2[] = "Out of message nodes";
const __flash char m3[] = "\n\nAll user processes have completed.\n\n";
const __flash char m4[] = "namespace: cannot mount %d\r\n";
const __flash char m5[] = "namespace: device name %s too long\r\n";
const __flash char m6[] = "Can't startup system";
const __flash char m7[] = "ptinit - insufficient memory";
const __flash char m8[] = "freemem: %10d bytes. Free-list:\n";
const __flash char m9[] = "Syscall not implemented\n";
const __flash char m10[] = "ERROR GETSTK %s\n";
const __flash char m11[] = "0x%08x    %d\n";
const __flash char m12[] = "looping... press reset\n";
const __flash char m13[] = "naminit (devices):\r\n";

