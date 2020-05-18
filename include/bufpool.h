/* bufpool.h */

#ifndef	NBPOOLS
// RAFA #define	NBPOOLS	20		/* Maximum number of buffer pools	*/
#define	NBPOOLS	5		/* Maximum number of buffer pools	*/
#endif

#ifndef	BP_MAXB
// #define	BP_MAXB	8192		/* Maximum buffer size in bytes		*/
#define	BP_MAXB	20		/* Maximum buffer size in bytes		*/
#endif

#define	BP_MINB	8		/* Minimum buffer size in bytes		*/
#ifndef	BP_MAXN
// RAFA #define	BP_MAXN	2048		/* Maximum number of buffers in a pool	*/
#define	BP_MAXN	10		/* Maximum number of buffers in a pool	*/
#endif

struct	bpentry	{		/* Description of a single buffer pool	*/
	struct	bpentry *bpnext;/* pointer to next free buffer		*/
	sid32	bpsem;		/* semaphore that counts buffers	*/
				/*    currently available in the pool	*/
	uint32	bpsize;		/* size of buffers in this pool		*/
	};

extern	struct	bpentry buftab[];/* Buffer pool table			*/
extern	bpid32	nbpools;	/* current number of allocated pools	*/
