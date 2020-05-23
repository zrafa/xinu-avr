/* strncpy.c - strncpy */

/*------------------------------------------------------------------------
 *  strncpy  -  Copy string s2 to s1, truncating or null-padding so that
 *			excatly n bytes are copied; return s1
 *------------------------------------------------------------------------
 */
char	*strncpy(
	  char		*s1,		/* First string			*/
	  const char	*s2,		/* Second string		*/
	  int		n		/* Length  to copy		*/
			)
{
    register int i;
    register char *os1;

    os1 = s1;
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
	blink_avr();
    kprintf("s1 0x%08X , s2 0x%08X\n\n", s1, s2);

    for (i = 0; i < n; i++)
    {
        if (((*s1++) = (*s2++)) == '\0')
        {
            while (++i < n)
            {
                *s1++ = '\0';
            }
            return os1;
        }
    }
    return os1;
}
