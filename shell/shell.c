/* shell.c  -  shell */

#include <xinu.h>
//#include <stdio.h>
#include "shprototypes.h"

/************************************************************************/
/* Table of Xinu shell commands and the function associated with each	*/
/************************************************************************/
// RAFA const	struct	cmdent	cmdtab[] = {

/************************************************************************/
/* shell  -  Provide an interactive user interface that executes	*/
/*	     commands.  Each command begins with a command name, has	*/
/*	     a set of optional arguments, has optional input or		*/
/*	     output redirection, and an optional specification for	*/
/*	     background execution (ampersand).  The syntax is:		*/
/*									*/
/*		   command_name [args*] [redirection] [&]		*/
/*									*/
/*	     Redirection is either or both of:				*/
/*									*/
/*				< input_file				*/
/*			or						*/
/*				> output_file				*/
/*									*/
/************************************************************************/

process	shell (
		did32	dev		/* ID of tty device from which	*/
	)				/*   to accept commands		*/
{
	kprintf("shell\n");
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
	return OK;
}

