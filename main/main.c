/*  main.c  - main */

/* shell.c  -  shell */


#include <xinu.h>
#include "shprototypes.h"

// #include <time.h>

// extern int set_date (char *s);
// extern int get_date (char *s);

void xsh_help(void);
shellcmd xsh_kill(int nargs, char *args[]);

typedef void (*CmdFunc_t)(char);
typedef struct cmdent cmdent_t;
/************************************************************************/
/* Table of Xinu shell commands and the function associated with each	*/
/************************************************************************/
// const struct	cmdent	cmdtab[] = {

const __flash uint8_t * const __flash cmdtab_cname[] =
{
  (const __flash uint8_t[]) { "memdump" },
  (const __flash uint8_t[]) { "editor" },
  (const __flash uint8_t[]) { "basic" },
  (const __flash uint8_t[]) { "help" },
  (const __flash uint8_t[]) { "sleep" },
  (const __flash uint8_t[]) { "forever" },
  (const __flash uint8_t[]) { "uptime" },
  (const __flash uint8_t[]) { "reboot" },
  (const __flash uint8_t[]) { "kill" },
  (const __flash uint8_t[]) { "free" },
  (const __flash uint8_t[]) { "clear" },
  (const __flash uint8_t[]) { "ps" },
  (const __flash uint8_t[]) { "echo" },
  (const __flash uint8_t[]) { "date" },
  (const __flash uint8_t[]) { "gpio" },
  (const __flash uint8_t[]) { "cal" }
};

const __flash uint8_t * const __flash cmdtab_help[] =
{
  (const __flash uint8_t[]) { ": display SRAM memory contents" },
  (const __flash uint8_t[]) { ": text editor" },
  (const __flash uint8_t[]) { ": BASIC language interpreter" },
  (const __flash uint8_t[]) { ": this help" },
  (const __flash uint8_t[]) { "n : sleep n seconds" },
  (const __flash uint8_t[]) { ": for (;;);" },
  (const __flash uint8_t[]) { ": tell how long the Xinu system has been running" },
  (const __flash uint8_t[]) { ": reset the Xinu system sw. THIS IS NOT a hw reset" },
  (const __flash uint8_t[]) { "n : kill (terminates) the n (ID) process" },
  (const __flash uint8_t[]) { ": display amount of free and used memory" },
  (const __flash uint8_t[]) { ": clear the terminal screen" },
  (const __flash uint8_t[]) { ": display current processes table" },
  (const __flash uint8_t[]) { "[arg ...] : write arguments to standard output" },
  (const __flash uint8_t[]) { "[MM/DD/YY HH:MM:SS] : set or get the date and time" },
  (const __flash uint8_t[]) { "p v : set the port p with value v" },
  (const __flash uint8_t[]) { "[mon] year : calendar" }
};
typedef int32	(*cmdfunc_t)(int32,char*[]);

const cmdent_t __flash cmdtab[] = {
	{FALSE,	xsh_memdump},
	{FALSE,	xsh_editor},
	{FALSE,	xsh_basic},
	{TRUE,	xsh_help},
	{FALSE,	xsh_sleep},
	{FALSE,	xsh_forever},
	{FALSE,	xsh_uptime},
	{FALSE,	xsh_reboot},
	{TRUE,	xsh_kill},
	{FALSE,	xsh_free},
	{TRUE,	xsh_clear},
	{TRUE,	xsh_ps},
	{FALSE,	xsh_echo},
	{FALSE,	xsh_date},
	{FALSE,	xsh_gpio},
	{FALSE,	xsh_cal}
};

const __flash int cmdtab_stk[] = {
	256,	/* memdump */
	400,	/* editor */
	400,	/* basic */
	128,	/* help */
	128,	/* sleep */
	128,	/* forever */
	200,	/* uptime */
	128,	/* reboot */
	300,	/* kill */
	128,	/* free */
	64,
	128,
	256,
	256,
	300,
	256,
};

//const __flash int32	(*f2)(int32,char*[]);
//struct cmdent p[2];


//shellcmd rafa(int a, char*args[]) {
//	printf("a:%d\n",a);
//}

const __flash char shell_commands[] = "\n\rCommands:\n\n\r";
const __flash char shell_init_msg[] = "\n\rfor a list of programs on this system type 'help'\nREADY\n\r";

void xsh_help(void) 
{
	int i;
	
	printf("%S", shell_commands);
	for (i=0; i<ncmd; i++) 
		printf(" %S %S\n", cmdtab_cname[i], cmdtab_help[i]);
	printf("\n\r");

}

//const struct	cmdent	cmdtab[] = {
//	{"memstat",	FALSE,	xsh_memstat}, /* Make built-in */
//	{"editor",	FALSE,	xsh_editor}, /* Make built-in */
//	{"basic",	FALSE,	xsh_basic}, /* Make built-in */
//	{"help",	TRUE,	xsh_help}, /* Make built-in */
//	{"echo",	FALSE,	xsh_echo}
//	{"argecho",	TRUE,	xsh_argecho},
//	{"cat",		FALSE,	xsh_cat},
//	{"clear",	TRUE,	xsh_clear},
//	{"date",	FALSE,	xsh_date},
//	{"devdump",	FALSE,	xsh_devdump},
//	{"echo",	FALSE,	xsh_echo},
//	{"exit",	TRUE,	xsh_exit},
//	{"help",	FALSE,	xsh_help},
//	{"kill",	TRUE,	xsh_kill},
//	{"memdump",	FALSE,	xsh_memdump},
//	{"ps",		FALSE,	xsh_ps},
//	{"sleep",	FALSE,	xsh_sleep},
//	{"uptime",	FALSE,	xsh_uptime},
//	{"?",		FALSE,	xsh_help}

//};

uint32	ncmd = sizeof(cmdtab) / sizeof(struct cmdent);

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

process	main(void)
{
	char	buf[SHELL_BUFLEN];	/* Input line (large enough for	*/
	int32	len;			/* Length of line read		*/
	char	tokbuf[SHELL_BUFLEN +	/* Buffer to hold a set of	*/
			SHELL_MAXTOK];  /* Contiguous null-terminated	*/
	int32	tlen;			/* Current length of all data	*/
					/*   in array tokbuf		*/
	int32	tok[SHELL_MAXTOK];	/* Index of each token in	*/
	int32	toktyp[SHELL_MAXTOK];	/* Type of each token in tokbuf	*/
	int32	ntok;			/* Number of tokens on line	*/
	pid32	child;			/* Process ID of spawned child	*/
	bool8	backgnd;		/* Run command in background?	*/
	char	*outname, *inname;	/* Pointers to strings for file	*/
					/*   names that follow > and <	*/
	did32	stdinput, stdoutput;	/* Descriptors for redirected	*/
					/*   input and output		*/
	int32	i;			/* Index into array of tokens	*/
	int32	j;			/* Index into array of commands	*/
	int32	msg;			/* Message from receive() for	*/
					/*   child termination		*/
	int32	tmparg;			/* Address of this var is used	*/
					/*   when first creating child	*/
					/*   process, but is replaced	*/
	char	*src, *cmp;		/* Pointers used during name	*/
					/*   comparison			*/
	bool8	diff;			/* Was difference found during	*/
	char	*args[SHELL_MAXTOK];	/* Argument vector passed to	*/
					/*   builtin commands		*/
	did32	dev = 0;		/* ID of tty device from which	*/

	char cname[8];

	change_proc_name("shell");

	/* Print shell banner and startup message */
/*
	fprintf(dev, "\n\n%s%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		SHELL_BAN0,SHELL_BAN1,SHELL_BAN2,SHELL_BAN3,SHELL_BAN4,
		SHELL_BAN5,SHELL_BAN6,SHELL_BAN7,SHELL_BAN8,SHELL_BAN9,SHELL_BAN10);

	fprintf(dev, "%s\n\n", SHELL_STRTMSG);
*/

	int len_p;

	/* eeprom
	char p[20];
	read("/dev/eeprom0", p, 19);
	p[19] = 0;
	printf("h:%s\n",p);
	read("EEPROM0", p, 19);
	p[19] = 0;
	printf("h:%s\n",p);
	*/

	/* Continually prompt the user, read input, and execute command	*/
	
//RAFA: for HORRIBLE WORKAROUND
	/* Entry in device switch table	*/
	const __flash struct dentry	*devptr;	
	/* Pointer to tty control block	*/
	struct	ttycblk	*typtr;		
	char *c;
// FIN RAFA

	while (TRUE) {


		/* Display prompt */
		fprintf(dev, SHELL_PROMPT);

			// HORRIBLE HACK FOR FOREVER BUG
			devptr = (struct dentry *) &devtab[0];
			typtr= &ttytab[devptr->dvminor];
			typtr->tyihead = typtr->tyitail = typtr->tyibuff;
			semreset(typtr->tyisem, 0);

		len = read(dev, buf, sizeof(buf));

		/* Exit gracefully on end-of-file */

		if (len == EOF) {
			break;
		}

		/* If line contains only NEWLINE, go to next line */

		if (len <= 1) {
			continue;
		}

		buf[len] = SH_NEWLINE;	/* terminate line */

		/* Parse input line and divide into tokens */

		ntok = lexan(buf, len, tokbuf, &tlen, tok, toktyp);

		/* Handle parsing error */

		if (ntok == SYSERR) {
			fprintf(dev,"%s\n", SHELL_SYNERRMSG);
			continue;
		}

		/* If line is empty, go to next input line */

		if (ntok == 0) {
			// fprintf(dev, "\n");
			continue;
		}

		/* If last token is '&', set background */

		if (toktyp[ntok-1] == SH_TOK_AMPER) {
			ntok-- ;
			tlen-= 2;
			backgnd = TRUE;
		} else {
			backgnd = FALSE;
		}


		/* Check for input/output redirection (default is none) */

		outname = inname = NULL;
		if ( (ntok >=3) && ( (toktyp[ntok-2] == SH_TOK_LESS)
				   ||(toktyp[ntok-2] == SH_TOK_GREATER))){
			if (toktyp[ntok-1] != SH_TOK_OTHER) {
				// fprintf(dev,"%s\n", SHELL_SYNERRMSG);
				continue;
			}
			if (toktyp[ntok-2] == SH_TOK_LESS) {
				inname =  &tokbuf[tok[ntok-1]];
			} else {
				outname = &tokbuf[tok[ntok-1]];
			}
			ntok -= 2;
			tlen = tok[ntok];
		}


		if ( (ntok >=3) && ( (toktyp[ntok-2] == SH_TOK_LESS)
				   ||(toktyp[ntok-2] == SH_TOK_GREATER))){
			if (toktyp[ntok-1] != SH_TOK_OTHER) {
				// fprintf(dev,"%s\n", SHELL_SYNERRMSG);
				continue;
			}
			if (toktyp[ntok-2] == SH_TOK_LESS) {
				if (inname != NULL) {
				    // fprintf(dev,"%s\n", SHELL_SYNERRMSG);
				    continue;
				}
				inname = &tokbuf[tok[ntok-1]];
			} else {
				if (outname != NULL) {
				    // fprintf(dev,"%s\n", SHELL_SYNERRMSG);
				    continue;
				}
				outname = &tokbuf[tok[ntok-1]];
			}
			ntok -= 2;
			tlen = tok[ntok];
		}

		/* Verify remaining tokens are type "other" */

		for (i=0; i<ntok; i++) {
			if (toktyp[i] != SH_TOK_OTHER) {
				break;
			}
		}
		if ((ntok == 0) || (i < ntok)) {
			// fprintf(dev, SHELL_SYNERRMSG);
			continue;
		}

		stdinput = stdoutput = dev;

		/* Lookup first token in the command table */

		for (j = 0; j < ncmd; j++) {
			cmp = tokbuf;
			//diff = FALSE;
			diff = TRUE;
			len_p = strlen_P(cmdtab_cname[j]);
			if (strncmp_P(cmp, cmdtab_cname[j], len_p) == 0 ) { 
				//diff = TRUE;
				diff = FALSE;
		};

			if (diff || (*(cmp+len_p) != NULLCH)) {
				continue;
			} else {
				break;
			}
		}

		/* Handle command not found */

		if (j >= ncmd) {
			fprintf(dev, "not found\n", tokbuf);
			continue;
		}

		/* Handle built-in command */

		if (cmdtab[j].cbuiltin) { /* No background or redirect. */
			if (inname != NULL || outname != NULL || backgnd){
				// fprintf(dev, SHELL_BGERRMSG);
				continue;
			} else {
				/* Set up arg vector for call */

				for (i=0; i<ntok; i++) {
					args[i] = &tokbuf[tok[i]];
				}

				/* Call builtin shell function */

				if ((*cmdtab[j].cfunc)(ntok, args)
							== SHELL_EXIT) {
					break;
				}
			}
			continue;
		}


		/* Open files and redirect I/O if specified */

		if (inname != NULL) {
			stdinput = open(NAMESPACE,inname,"ro");
			if (stdinput == SYSERR) {
				// fprintf(dev, SHELL_INERRMSG, inname);
				continue;
			}
		}
		if (outname != NULL) {
			stdoutput = open(NAMESPACE,outname,"w");
			if (stdoutput == SYSERR) {
				// fprintf(dev, SHELL_OUTERRMSG, outname);
				continue;
			} else {
				control(stdoutput, F_CTL_TRUNC, 0, 0);
			}
		}

		/* Spawn child thread for non-built-in commands */

		strncpy_P(cname, cmdtab_cname[j], len_p);
		cname[len_p] = 0;
		child = create(cmdtab[j].cfunc,
			cmdtab_stk[j], SHELL_CMDPRIO,
			cname, 2, ntok, &tmparg);

		/* If creation or argument copy fails, report error */

		if ((child == SYSERR) ||
		    (addargs(child, ntok, tok, tlen, tokbuf, &tmparg)
							== SYSERR) ) {
			// fprintf(dev, SHELL_CREATMSG);
			fprintf(dev, "?\n\r");
			continue;
		}

		/* Set stdinput and stdoutput in child to redirect I/O */

		proctab[child].prdesc[0] = stdinput;
		proctab[child].prdesc[1] = stdoutput;

		msg = recvclr();
		resume(child);

		if (! backgnd) {
			msg = receive();
			while (msg != child) {
				msg = receive();
			}
		}
    }

    /* Terminate the shell process by returning from the top level */

    // fprintf(dev,SHELL_EXITMSG);
    return OK;
}
