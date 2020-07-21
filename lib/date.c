/* date.c: set and get the locate date and time */

#include <xinu.h>
#include <stdint.h>

// typedef long unsigned int size_t;
typedef uint32_t time_t;

#include <time.h>

time_t seconds;
extern uint32 clktime;

int get_date(char * s) 
{
	struct tm avr_tm;
	time_t sec;

	sec = seconds + clktime;
 	localtime_r(&sec, &avr_tm);
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

 	/* FIXME - WARNING: interrupts should be disable before */
	seconds = mktime(&avr_tm) - clktime;

	return 0;
}

