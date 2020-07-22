/* kernel.h */

/* avr specific values. Original saved under orig/ folder */

/* General type declarations used throughout the kernel */

typedef	unsigned char	byte;
typedef	unsigned char	uint8;
typedef	long		int32;
typedef	int		int16;
typedef	unsigned long	uint32;
typedef	unsigned int	uint16;
typedef	unsigned long long uint64;

/* Xinu-specific types */

typedef	int16	pri16;		/* process priority			*/
typedef	uint32	umsg32;		/* message passed among processes	*/
typedef	int32	bpid32;		/* buffer pool ID			*/
typedef	byte	bool8;		/* Boolean type				*/

/* Xinu-specific types */

typedef int   sid32;          /* semaphore ID                         */
typedef int16   qid16;          /* queue ID                             */
typedef int32   pid32;          /* process ID                           */
typedef int32   did32;          /* device ID                            */
// typedef uint32  intmask;        /* saved interrupt mask                 */
typedef uint8  intmask;        /* saved interrupt mask                 */
typedef int32   ibid32;         /* index block ID (used in file system) */
typedef int32   dbid32;         /* data block ID (used in file system)  */
typedef int32   uid32;          /* ID for UDP table descriptor          */


//typedef	char	sid32;		/* semaphore ID				*/
//typedef	char	qid16;		/* queue ID				*/
//typedef	char	pid32;		/* process ID				*/
//typedef	char	did32;		/* device ID				*/
//typedef	char	intmask;	/* saved interrupt mask			*/
//typedef	char	ibid32;		/* index block ID (used in file system)	*/
//typedef	char	dbid32;		/* data block ID (used in file system)	*/
//typedef	char	uid32;		/* ID for UDP table descriptor		*/

/* Function declaration return types */

typedef int32	process;	/* top-level function of a process	*/
typedef	void	interrupt;	/* interrupt procedure			*/

typedef char	syscall;	/* system call declaration		*/
typedef char	devcall;	/* device call declaration		*/
typedef char	shellcmd;	/* shell command declaration		*/
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

#define	MINSTK	64		/* minimum stack size in bytes		*/

#define	CONTEXT	64		/* bytes in a function call context on	*/
				/* the run-time stack			*/
#define	QUANTUM	1		/* time slice in milliseconds		*/

/* Size of the stack for the null process */

#define	NULLSTK		64	/* stack size for null process		*/

/* Prototypes of I/O functions used throughout the kernel */

syscall	kprintf(char *fmt, ...);
syscall	kputc(byte);
syscall	kgetc(void);
