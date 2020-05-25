/*
 *  ctxsw.S - ctxsw
 *  avr-Xinu
 *
 *  Created by Michael Minor on 12/7/08.
 *  Copyright 2010. All rights reserved.
 *
 */


/*----------------------------------------------------------------------------------------*/
/*   ctxsw -- actually perform context switch, saving and loading registers               */
/*----------------------------------------------------------------------------------------*/


;  void ctxsw(char *old_pregs, char *new_pregs);
; The stack contains the return address upon entry to this routine, and
;
;		R25 => address of save area with OLD registers + PS
;		R24 => address of save area (low)
;		R23 => address of save area with NEW registers + PS
;		R22 => address of save area (low byte)
;
;
; The saved state consists of the values of R0-R31 upon entry, SP_L, SP_H,
; PC_L, PC_H, equal to the return address, and the PS (SREG)
;
; Save image: r0,r1,r2,r3,r4,r5,r6,...,r26,r27,r28,r29,r30,r31,SP_L,SP_H,PC_L,PC_H,SREG,0x00
;              0  1  2  3  4  5  6 ...  26  27  28  29  30  31   32   33   34   35   36,  37
	
	
	
	.set __SREG__,0x3f	; Status register
	.set __SP_H__,0x3e	; Stack pointer high
	.set __SP_L__,0x3d	; Stack pointer low
	.global ctxsw
	
ctxsw:
	push r31
	push r30
	movw r30,r24	; get first argument
	std Z+0,r0		; save r0
	in r0,__SREG__	; get SREG
	cli				; disable interrupts
	std Z+36,r0		; save SREG	
	std Z+1,r1		; save r1
	std Z+2,r2		; save r2
	std Z+3,r3
	std Z+4,r4
	std Z+5,r5
	std Z+6,r6
	std Z+7,r7
	std Z+8,r8
	std Z+9,r9
	std Z+10,r10	; ...
	std Z+11,r11
	std Z+12,r12
	std Z+13,r13
	std Z+14,r14
	std Z+15,r15
	std Z+16,r16
	std Z+17,r17
	std Z+18,r18
	std Z+19,r19
	std Z+20,r20
	std Z+21,r21
	std Z+22,r22
	std Z+23,r23
	std Z+24,r24
	std Z+25,r25
	std Z+26,r26
	std Z+27,r27
	std Z+28,r28	; save r28
	std Z+29,r29	; save r29
	pop r0			; get saved r30
	std Z+30,r0		; save r30
	pop r0			; get saved r31
	std Z+31,r0		; save r31
	in r0,__SP_L__	; get SP_L
	std Z+32,r0		; save
	in r0,__SP_H__	; get SP_H
	std Z+33,r0		; save	

	movw r30,r22	; get address of new process save area
	ldd r0,Z+32		; get SP_L
	out __SP_L__,r0	; load new SP -- SWITCH STACKS
	ldd r0,Z+33
	out __SP_H__,r0
	
	ldd r0,Z+31		; get saved r31
	push r0			; save r31
	ldd r0,Z+30		; get saved r30
	push r0			; save r30
	ldd r29,Z+29	; load r29
	ldd r28,Z+28	; load r28
	ldd r27,Z+27	; ...
	ldd r26,Z+26
	ldd r25,Z+25
	ldd r24,Z+24
	ldd r23,Z+23
	ldd r22,Z+22
	ldd r21,Z+21
	ldd r20,Z+20
	ldd r19,Z+19
	ldd r18,Z+18
	ldd r17,Z+17
	ldd r16,Z+16
	ldd r15,Z+15
	ldd r14,Z+14
	ldd r13,Z+13
	ldd r12,Z+12
	ldd r11,Z+11
	ldd r10,Z+10
	ldd r9,Z+9
	ldd r8,Z+8
	ldd r7,Z+7
	ldd r6,Z+6
	ldd r5,Z+5
	ldd r4,Z+4
	ldd r3,Z+3
	ldd r2,Z+2		; ...
	ldd r1,Z+1		; load r1
	ldd r0,Z+36		; get saved SREG
	out __SREG__,r0	; restore SREG - may enable interrupts
	ldd r0,Z+0		; load r0
	pop r30			; load r30 & r31
	pop r31	
	ret				; load PC, and execute new process
	
	
