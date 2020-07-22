/* naminit.c - naminit */

#include <xinu.h>

#ifndef	RFILESYS
#define	RFILESYS	SYSERR
#endif

#ifndef	FILESYS
#define	FILESYS		SYSERR
#endif

#ifndef	LFILESYS
#define	LFILESYS	SYSERR
#endif

struct	nmentry	nametab[NNAMES];	/* Table of name mappings	*/
int32	nnames;				/* Number of entries allocated	*/

/*------------------------------------------------------------------------
 *  naminit  -  Initialize the syntactic namespace
 *------------------------------------------------------------------------
 */
status	naminit(void)
{
	did32	i;			/* Index into devtab		*/
	// struct	dentry *devptr;		/* Pointer to device table entry*/
	const __flash struct	dentry *devptr;		/* Pointer to device table entry*/
	char	tmpstr[NM_MAXLEN];	/* String to hold a name	*/
	status	retval;			/* Return value			*/
	char	*tptr;			/* Pointer into tempstring	*/
	char	*nptr;			/* Pointer to device name	*/
	char	devprefix[] = "/dev/";	/* Prefix to use for devices	*/
	int32	len;			/* Length of created name	*/
	char	ch;			/* Storage for a character	*/

	/* Set prefix table to empty */

	nnames = 0;

	// RAFA 
	/* avr specific */
	char name[10];
	avr_kprintf(m13);

	for (i=0; i<NDEVS ; i++) {
		tptr = tmpstr;
		nptr = devprefix;

		/* Copy prefix into tmpstr */

		len = 0;
		while ((*tptr++ = *nptr++) != NULLCH) {
			len++;
	        }
                tptr--; /* Move pointer to position before NULLCH */
		devptr = &devtab[i];
		nptr = devptr->dvname;	/* Move to device name */
		/* avr specific */
		strncpy_P(name, devptr->dvname, 10);
		nptr = name;

		/* Map device name to lower case and append */

		while(++len < NM_MAXLEN) {
			ch = *nptr++;
			if ( (ch >= 'A') && (ch <= 'Z')) {
				ch += 'a' - 'A';
			}
			if ( (*tptr++ = ch) == NULLCH) {
				break;
			}
		}

		if (len > NM_MAXLEN) {
			avr_kprintf(m5);
			continue;
		}

		// RAFA
		kprintf("  %s\n",tmpstr);

		retval = mount(tmpstr, NULLSTR, devptr->dvnum);
                if (retval == SYSERR) {
			avr_kprintf(m4);
			continue;
		}
	}

	/* Add other prefixes (longest prefix first) */

//      mount("/dev/null",	"",        NULLDEV);
//	mount("/remote/",	"remote:", RFILESYS);
//	mount("/local/",	NULLSTR,   LFILESYS);
	mount("/dev/",		NULLSTR,   SYSERR);
//      mount("~/",		NULLSTR,   LFILESYS);
//	mount("/",		"root:",   RFILESYS);
//	mount("",		"",        LFILESYS);

	return OK;
}
