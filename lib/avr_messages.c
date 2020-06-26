
/* avr specific */

typedef unsigned int size_t;
#include <avr/pgmspace.h>

/*
const char m0[] PROGMEM = "\nWelcome to Xinu!\n\n\r\tXinu OS Copyright (c) 2012, 2015\n\r\tDouglas E. Comer and CRC Press, Inc.\n\n\r\tThis version for AVR atmega328p v0.1 (c) 2020\n\r\tRafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>\n\n\r";
const char m1[] PROGMEM = "\n\nRecreating shell\n\n";
const char m2[] PROGMEM = "Out of message nodes";
const char m3[] PROGMEM = "\n\nAll user processes have completed.\n\n";
const char m4[] PROGMEM = "namespace: cannot mount %d\r\n";
const char m5[] PROGMEM = "namespace: device name %s too long\r\n";
const char m6[] PROGMEM = "Can't startup system";
const char m7[] PROGMEM = "ptinit - insufficient memory";
const char m8[] PROGMEM = "freemem: %10d bytes. Free-list:\n";
const char m9[] PROGMEM = "Syscall not implemented\n";
const char m10[] PROGMEM = "ERROR GETSTK %s\n";
const char m11[] PROGMEM = "0x%08x    %d\n";
const char m12[] PROGMEM = "looping... press reset\n";
*/

const __flash char sysinit_m0[] = "\nWelcome to Xinu!\n\n\r\tXinu OS Copyright (c) 2012, 2015\n\r\tDouglas E. Comer and CRC Press, Inc.\n\n\r\tThis version for AVR atmega328p v0.1 (c) 2020\n\r\tRafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>\n\n\r";
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

