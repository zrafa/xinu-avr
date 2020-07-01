#include <stdint.h>

typedef long int32;
typedef unsigned long uint32;
typedef long unsigned int size_t;


typedef uint32_t time_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

struct tm avr_tm;
char days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/*
const char * strp_weekdays[] = 
    { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
const char * strp_monthnames[] = 
    { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
*/

#define SECONDS_PER_DAY (60*60*24)

unsigned long int seconds = 0;
unsigned int days = 0;

// unsigned long long int seconds = 0;

int date(const char *s) {

	int m, d, y;
	int hour, min, sec;
	int i;
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
	// y = 2000 + atoi(two);
	y = atoi(two);

/*
	while (isspace((int)(*s))) 
		++s;
*/
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

	for (i=2000; i<y; i++) {
		if ( i % 4 == 0 && i % 100 != 0 || i % 400 == 0 )
			days = days + 366;
			//seconds = seconds + (366 * SECONDS_PER_DAY);
    		else
			days = days + 365;
			//seconds = seconds + (365 * SECONDS_PER_DAY);
	}
	for (i=1; i<m; i++) {
		days = days + days_per_month[i-1];
		//seconds = seconds + (days_per_month[i-1] * SECONDS_PER_DAY);
		if ((i == 2) && ( y % 4 == 0 && y % 100 != 0 || y % 400 == 0 ))
			days++;
			//seconds = seconds + (SECONDS_PER_DAY);
	}
	days = days + d;
	//seconds = seconds + (d * SECONDS_PER_DAY);
	seconds = 0;
	seconds = seconds + (hour * 3600) + (min * 60) + sec;
	printf("h:%d\n", hour);
	printf("m:%d\n", min);
	printf("s:%d\n", sec);
	printf("d:%d\n", d);
	printf("m:%d\n", m);
	printf("y:%d\n", y);
	avr_tm.tm_sec = sec;
	avr_tm.tm_min = min;
	avr_tm.tm_hour = hour;
	avr_tm.tm_mon = m - 1;
	avr_tm.tm_mday = d;
	avr_tm.tm_year = y + 100;


	return 0;
}



const unsigned int dinamonth[13] = {0,0,0,31,30,31,30,31,31,30,31,30,31};    
//const unsigned long secinamonth[13] = {0,0,0,31*86400,30*86400,31*86400,30*86400,31*86400,31*86400,30*86400,31*86400,30*86400,31*86400};    

void seconds_to_date(int *y, int *m, int *d, int *h, int *min, int *s)                  // unsigned 32bit input 
{
	unsigned long int dd = days;
	unsigned long int ss = seconds;
	
	
	
  char temp = 0;                                        // start at year 2000
  while (dd >= 1460 && temp <100) { dd -= 1460; temp +=4;} // four year blocks until 2100
  // while (sec >= 126230400 && temp <100) { sec -= 126230400; temp +=4;} // four year blocks until 2100
  if (temp == 100){while (dd >= 366 && temp <104){ dd -= 366; temp +=1;}}//no leapyears
  //if (temp == 100){while (sec >= 31536000 && temp <104){ sec -= 31536000; temp +=1;}}//no leapyears
  while (dd >= 1460){ dd -= 1460; temp +=4;}// four year blocks again
  //while (sec >= 126230400){ sec -= 126230400; temp +=4;}// four year blocks again
  if (dd >= 366){ dd -= 366; temp +=1;      // first year after a 4yr block is a leapyear                           
  // if (sec >= 31622400){ sec -= 31622400; temp +=1;      // first year after a 4yr block is a leapyear                           
    while (dd >= 366){ dd -= 366; temp +=1;}// then it can only be two years left 
    // while (sec >= 31536000){ sec -= 31536000; temp +=1;}// then it can only be two years left 
  } 
  *y = temp; temp = 1;                             // let it go past 99 to max 136 for year 2136
 
  if (dd >= 31){                                  // January
  //if (sec >= 86400*31){                                  // January
    dd -= 31; temp +=1;                          
    int tempfeb = 28;
    if (*y !=100 && !(*y & 3)) tempfeb = 29;// 2100 is no leap year
    //if (rtc.year !=100 && !(rtc.year & 3)) tempfeb = 29;// 2100 is no leap year
    if (dd >= tempfeb){ 
    //if (sec >= tempfeb){ 
      dd -= tempfeb; temp +=1;                          // do the other months now
     // sec -= tempfeb; temp +=1;                          // do the other months now
      while (dd >= dinamonth[temp]){ dd -= dinamonth[temp]; temp +=1;}
      //while (sec >= secinamonth[temp]){ sec -= secinamonth[temp]; temp +=1;}
    }
  }
  *m = temp; temp = 1;
 
  while (dd >= 1){ dd -= 1; temp +=1;}         // days
  *d = temp; temp = 0;
  while (ss >= 3600){ ss -= 3600; temp +=1;}           // hour
  *h = temp; temp = 0;
  while (ss >= 60){ ss -= 60; temp +=1;}               // minute
  *min = temp; 
  *s = ss;                                      // seconds
}
