/* kernel.h */

/* General type declarations used throughout the kernel */

typedef	unsigned char	byte;
typedef	unsigned char	uint8;
typedef	int		int32;
typedef	short		int16;
typedef	unsigned int	uint32;
typedef	unsigned short	uint16;
typedef	unsigned long long uint64;

/* Xinu-specific types */

// RAFA typedef	int32	sid32;		/* semaphore ID				*/
// RAFA typedef	int16	qid16;		/* queue ID				*/
// RAFA typedef	int32	pid32;		/* process ID				*/
// RAFA typedef	int32	did32;		/* device ID				*/
// RAFA typedef	int16	pri16;		/* process priority			*/
// RAFA typedef	uint32	umsg32;		/* message passed among processes	*/
// RAFA typedef	int32	bpid32;		/* buffer pool ID			*/
// RAFA typedef	byte	bool8;		/* Boolean type				*/
// RAFA typedef	uint32	intmask;	/* saved interrupt mask			*/
// RAFA typedef	int32	ibid32;		/* index block ID (used in file system)	*/
// RAFA typedef	int32	dbid32;		/* data block ID (used in file system)	*/
// RAFA typedef	int32	uid32;		/* ID for UDP table descriptor		*/

typedef	char	sid32;		/* semaphore ID				*/
typedef	char	qid16;		/* queue ID				*/
typedef	char	pid32;		/* process ID				*/
typedef	char	did32;		/* device ID				*/
typedef	char	pri16;		/* process priority			*/
typedef	char	umsg32;		/* message passed among processes	*/
typedef	char	bpid32;		/* buffer pool ID			*/
typedef	byte	bool8;		/* Boolean type				*/
typedef	char	intmask;	/* saved interrupt mask			*/
typedef	char	ibid32;		/* index block ID (used in file system)	*/
typedef	char	dbid32;		/* data block ID (used in file system)	*/
typedef	char	uid32;		/* ID for UDP table descriptor		*/

/* Function declaration return types */

// RAFA typedef int32	syscall;	/* system call declaration		*/
// RAFA typedef int32	devcall;	/* device call declaration		*/
// RAFA typedef int32	shellcmd;	/* shell command declaration		*/
// RAFA typedef int32	process;	/* top-level function of a process	*/
// RAFA typedef	void	interrupt;	/* interrupt procedure			*/
// RAFA typedef	int32	status;		/* returned status value (OK/SYSERR)	*/

typedef char	syscall;	/* system call declaration		*/
typedef char	devcall;	/* device call declaration		*/
typedef char	shellcmd;	/* shell command declaration		*/
typedef char	process;	/* top-level function of a process	*/
typedef	void	interrupt;	/* interrupt procedure			*/
typedef	char	status;		/* returned status value (OK/SYSERR)	*/

#define local	static		/* Local procedure or variable declar.	*/

/* Boolean constants */

#define FALSE	0		/* Boolean False			*/
#define TRUE	1		/* Boolean True				*/

/* Null pointer, character, and string definintions */

#define NULL	0		/* null pointer for linked lists	*/
#define NULLCH	'\0'		/* null character			*/
#define	NULLSTR	""		/* null string				*/

/* Universal return constants */

#define OK	( 1)		/* normal system call return		*/
#define	SYSERR	(-1)		/* system call failed			*/
#define	EOF	(-2)		/* End-of-file (usually from read)	*/
#define	TIMEOUT	(-3)		/* system call timed out		*/

extern	qid16	readylist;	/* global ID for list of ready processes*/

// RAFA #define	MINSTK	400		/* minimum stack size in bytes		*/
#define	MINSTK	100		/* minimum stack size in bytes		*/

#define	CONTEXT	64		/* bytes in a function call context on	*/
				/* the run-time stack			*/
#define	QUANTUM	1		/* time slice in milliseconds		*/

/* Size of the stack for the null process */

// #define	NULLSTK		4096	/* stack size for null process		*/
#define	NULLSTK		256	/* stack size for null process		*/

/* Prototypes of I/O functions used throughout the kernel */

syscall	kprintf(char *fmt, ...);
syscall	kputc(byte);
syscall	kgetc(void);
