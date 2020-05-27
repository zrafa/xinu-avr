/* process.h - isbadpid */

/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		4
#endif		

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

// RAFA #define	PNMLEN		16	/* Length of process "name"		*/
#define	PNMLEN		8	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

// RAFA para AVR
#define PNREGS          38              /* size of saved register area  */
#define SSP_L           32              /* saved SP (low)               */
#define SSP_H           33              /* saved SP (high)                              */
#define SPC_L           34              /* saved PC (low)               */
#define SPC_H           35              /* saved PC (high)              */
#define SSREG           36              /* saved Status Register        */

#define	INITPS		0x80	/* initial process SREG (interrupts enabled)	*/
// RAFA #define MAXARG		6
#define MAXARG		4
#define	INITREG		0




/* Process initialization constants */

// #define	INITSTK		4096	/* Initial process stack size		*/
#define	INITSTK		64	/* Initial process stack size		*/
#define	INITPRIO	20	/* Initial process priority		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= NPROC) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */

struct procent {		/* Entry in the process table		*/
	uint16	prstate;	/* Process state: PR_CURR, etc.		*/
	pri16	prprio;		/* Process priority			*/
	unsigned char pregs[PNREGS];/* saved context (see ctxsw)	*/

	int pargs;				/* initial number of arguments	*/
	// int parg[MAXARG];	/* arguments					*/
	void * parg[MAXARG];	/* arguments					*/
	int *paddr;			/* initial code address			*/

	char	*prstkptr;	/* Saved stack pointer			*/
	unsigned char	*prstkbase;	/* Base of run time stack		*/
	uint32	prstklen;	/* Stack length in bytes		*/
	char	prname[PNMLEN];	/* Process name				*/
	sid32	prsem;		/* Semaphore on which process waits	*/
	pid32	prparent;	/* ID of the creating process		*/
	umsg32	prmsg;		/* Message sent to this process		*/
	bool8	prhasmsg;	/* Nonzero iff msg is valid		*/
	int16	prdesc[NDESC];	/* Device descriptors for process	*/
};

/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/
