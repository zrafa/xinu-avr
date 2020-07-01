/* xsh_cal.c - xsh_cal */

#include <xinu.h>
#include <stdio.h>

const __flash char	dayw[] = {
	" S  M Tu  W Th  F  S"
};
/*
const __flash char	*smon[]= {
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec",
};
*/

const __flash uint8_t * const __flash smon[] =
{
(const __flash uint8_t[]) { "Jan" },
(const __flash uint8_t[]) { "Feb" },
(const __flash uint8_t[]) { "Mar" },
(const __flash uint8_t[]) { "Apr" },
(const __flash uint8_t[]) { "May" },
(const __flash uint8_t[]) { "Jun" },
(const __flash uint8_t[]) { "Jul" },
(const __flash uint8_t[]) { "Aug" },
(const __flash uint8_t[]) { "Sep" },
(const __flash uint8_t[]) { "Oct" },
(const __flash uint8_t[]) { "Nov" },
(const __flash uint8_t[]) { "Dec" }
};

/*------------------------------------------------------------------------
 * xsh_cal - calendar
 *------------------------------------------------------------------------
 */

shellcmd xsh_cal(int nargs, char *args[])

{
//	char	string[4];
	register y, i, j;
	int m;

	if(nargs < 2) {
	//	printf("usage: cal [month] year\n");
		exit(0);
	}
	if(nargs == 2)
		goto xlong;

/*
 *	print out just month
 */

	m = number(args[1]);
	if(m<1 || m>12)
		goto badarg;
	y = number(args[2]);
	if(y<1 || y>9999)
		goto badarg;
	printf("\n   %S ", smon[m-1]);
	printf("%u\n", y);
	printf("%S\n", dayw);
	// cal_p(m, y, string, 24);
	cal_p(m, y);
	printf("\n");
	exit(0);

/*
 *	print out complete year
 */

xlong:
	y = number(args[1]);
	if(y<1 || y>9999)
		goto badarg;
	for(i=1; i<=12; i++) {
		printf("\n   %S ", smon[i-1]);
		printf("%u\n", y);
		printf("%S\n", dayw);
		// cal_p(i, y, string, 24);
		cal_p(i, y);
	}

	printf("\n");
	exit(0);

badarg:
	printf("Bad argument\n");
}

number(str)
char *str;
{
	register n, c;
	register char *s;

	n = 0;
	s = str;
	while(c = *s++) {
		if(c<'0' || c>'9')
			return(0);
		n = n*10 + c-'0';
	}
	return(n);
}

char	mon[] = {
	0,
	31, 29, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31,
};


/*
 *	return day of the week
 *	of jan 1 of given year
 */

jan1(yr)
{
	register y, d;

/*
 *	normal gregorian calendar
 *	one extra day per four years
 */

	y = yr;
	d = 4+y+(y+3)/4;

/*
 *	julian calendar
 *	regular gregorian
 *	less three days per 400
 */

	if(y > 1800) {
		d -= (y-1701)/100;
		d += (y-1601)/400;
	}

/*
 *	great calendar changeover instant
 */

	if(y > 1752)
		d += 3;

	return(d%7);
}

print_spaces(int d) {
	int i;
	for (i=1; i<d; i++)
		printf(" ");

}

cal_p(m, y)
{
	register d, i;
	register char *s;

	// s = p;
	d = jan1(y);
	mon[2] = 29;
	mon[9] = 30;

	switch((jan1(y+1)+7-d)%7) {

	/*
	 *	non-leap year
	 */
	case 1:
		mon[2] = 28;
		break;

	/*
	 *	1752
	 */
	default:
		mon[9] = 19;
		break;

	/*
	 *	leap year
	 */
	case 2:
		;
	}
	for(i=1; i<m; i++)
		d += mon[i];
	d %= 7;
//	s += 3*d;
	print_spaces(3*d+1);
	for(i=1; i<=mon[m]; i++) {
		if(i==3 && mon[m]==19) {
			i += 11;
			mon[m] += 11;
		}
		if(i > 9)
			// *s = i/10+'0';
			printf("%c", i/10+'0');
		else
			printf(" ");
		//s++;
//		printf(" ");
		// *s++ = i%10+'0';
		printf("%c", i%10+'0');
		// s++;
		printf(" ");
		if(++d == 7) {
			d = 0;
			// s = p+w;
//			print_spaces(p+w);
			printf("\n");
			//p = s;
		}
	}
	printf("\n");
}

