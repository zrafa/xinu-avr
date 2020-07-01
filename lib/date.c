#include <stdint.h>

typedef long unsigned int size_t;

typedef uint32_t time_t;

#include <time.h>

time_t seconds;
//time_t sec_stamp;

extern clktime;

int get_date(char * s) 
{
	struct tm avr_tm;

//	seconds = seconds + (clktime - sec_stamp);
	seconds = seconds + clktime;
	localtime_r(&seconds, &avr_tm);
	asctime_r(&avr_tm, s);
}

int set_date(const char *s) 
{
	struct tm avr_tm;

	int m, d, y;
	int hour, min, sec;
	char two[3];

	two[2] = 0;

	/* month */
	two[0] = *s; s++; two[1] = *s; s++;
	m = atoi(two);

	s++;

	/* day */
	two[0] = *s; s++; two[1] = *s; s++;
	d = atoi(two);

	s++;

	/* year */
	two[0] = *s; s++; two[1] = *s; s++;
	y = atoi(two);

	s++;
	
	/* hour */
	two[0] = *s; s++; two[1] = *s; s++;
	hour = atoi(two);

	s++;

	/* minutes */
	two[0] = *s; s++; two[1] = *s; s++;
	min = atoi(two);

	s++;

	/* seconds */
	two[0] = *s; s++; two[1] = *s; s++;
	sec = atoi(two);

	avr_tm.tm_sec = sec;
	avr_tm.tm_min = min;
	avr_tm.tm_hour = hour;
	avr_tm.tm_mon = m - 1;
	avr_tm.tm_mday = d;
	avr_tm.tm_year = y + 100;
	avr_tm.tm_isdst = 0;

	// seconds = mktime(&avr_tm);
	seconds = mktime(&avr_tm) - clktime;

//	sec_stamp = clktime; /* WARNING: interrupts should be disable before */

	return 0;
}



