/* memory.h - roundmb, truncmb, freestk */

#define	PAGE_SIZE	1024 // TODO: unused?

/*----------------------------------------------------------------------
 * roundmb, truncmb - Round or truncate address to memory block size
 *----------------------------------------------------------------------
 */
#define	roundmb(x)	(char *)( (7 + (uint32)(x)) & (~7) )
#define	truncmb(x)	(char *)( ((uint32)(x)) & (~7) )

/*----------------------------------------------------------------------
 *  freestk  --  Free stack memory allocated by getstk
 *----------------------------------------------------------------------
 */
#define	freestk(p,len)	freemem((char *)((uint32)(p)		\
				- ((uint32)roundmb(len))	\
				+ (uint32)sizeof(uint32)),	\
				(uint32)roundmb(len) )

struct	memblk	{			/* See roundmb & truncmb	*/
	struct	memblk	*mnext;		/* Ptr to next free memory blk	*/
	uint32	mlength;		/* Size of blk (includes memblk)*/
	};
extern	struct	memblk	memlist;	/* Head of free memory list	*/
extern	void	*minheap;		/* Start of heap		*/
extern	void	*maxheap;		/* Highest valid heap address	*/


/* Added by linker */

// extern	uint32	text;			/* Start of text segment	*/
// extern	uint32	etext;			/* End of text segment		*/
// extern	uint32	data;			/* Start of data segment	*/
// extern	uint32	edata;			/* End of data segment		*/
// extern	uint32	bss;			/* Start of bss segment		*/
// extern	uint32	ebss;			/* End of bss segment		*/
// extern	uint32	end;			/* End of program		*/
