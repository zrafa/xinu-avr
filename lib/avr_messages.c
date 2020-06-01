
/* avr specific */

typedef unsigned int size_t;
#include <avr/pgmspace.h>

// const char CONSOLE_RESET[] PROGMEM = " \033[0m\033[2J\033[;H";
// const char m0[] PROGMEM = "Welcome to Xinu for AVR microcontrollers!\n v0.1 rafa@fi.uncoma.edu.ar";
const char m1[] PROGMEM = "\n\nMain process recreating shell\n\n";
const char m2[] PROGMEM = "Port system ran out of message nodes";
const char m3[] PROGMEM = "\n\nAll user processes have completed.\n\n";
const char m4[] PROGMEM = "namespace: cannot mount device %d\r\n";
const char m5[] PROGMEM = "namespace: device name %s too long\r\n";
const char m6[] PROGMEM = "Can't startup system";
const char m7[] PROGMEM = "ptinit - insufficient memory";
const char m8[] PROGMEM = "free mem: %10d bytes. Free-list:\n";
const char m9[] PROGMEM = "System call not implemented\n";
const char m10[] PROGMEM = "ERROR GETSTK %s\n";
const char m11[] PROGMEM = "0x%08x    %d\n";
const char m12[] PROGMEM = "looping... press reset\n";

