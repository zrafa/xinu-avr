/* avr specific */
/* We do a hack for calling (insert) nulluser before main,
 * so avr-libc does everything : ld scripts, startup, etc 
 */
#include <avr/io.h>

.weak __heap_end
.set  __heap_end, 0

.macro vector name
    .weak \name
    .set \name, __vectors
    jmp \name
.endm

.section .vectors
__vectors:
    jmp __ctors_end
    vector __vector_1
    vector __vector_2
    vector __vector_3
    vector __vector_4
    vector __vector_5
    vector __vector_6
    vector __vector_7
    vector __vector_8
    vector __vector_9
    vector __vector_10
    vector __vector_11
    vector __vector_12
    vector __vector_13
    vector __vector_14
    vector __vector_15
    vector __vector_16
    vector __vector_17
    vector __vector_18
    vector __vector_19
    vector __vector_20
    vector __vector_21
    vector __vector_22
    vector __vector_23
    vector __vector_24
    vector __vector_25

.section .init8
    jmp nulluser
