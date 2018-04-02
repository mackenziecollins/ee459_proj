//PCF8563.h


//PCF8563.h

/*****
 *  NAME
 *    External Real Time Clock support routines
 *  AUTHOR
 *    Joe Robertson, jmr
 *    orbitalair@bellsouth.net
 *    
 *  CREATION DATE
 *    1/2/10,  init - built off of pic rtc code
 *  NOTES
 *  HISTORY
 *    1/2/10  ported to arduino compiler, jmr
 *    2/14/10 added 3 world date formats, jmr
 *    28/02/2012 A. Pasotti
 *            fixed a bug in RTCC_ALARM_AF,
 *            added a few (not really useful) methods
 *    12/26/12 added version method to be able to track builds. jmr
 *             fix for arduino 1.0.1. Wire.
 *    
 *  TODO
 *
 ******
 *  Robodoc embedded documentation.
 *  http://www.xs4all.nl/~rfsber/Robo/robodoc.html
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "i2c.h"

// #define RTCC_VERSION  "Pcf8563 v1.0.3"

/* the read and write values for pcf8563 rtcc */
/* these are adjusted for arduino */
#define B(x) S_to_binary_(#x)

#define RTCC_R 	0xa3
#define RTCC_W 	0xa2
#define Rtcc_Addr RTCC_W

#define RTCC_SEC 			1
#define RTCC_MIN 			2
#define RTCC_HR 			3
#define RTCC_DAY 			4
#define RTCC_WEEKDAY	5
#define RTCC_MONTH 		6
#define RTCC_YEAR 		7
#define RTCC_CENTURY 	8

/* register addresses in the rtc */
#define RTCC_STAT1_ADDR			0x00
#define RTCC_STAT2_ADDR			0x01
#define RTCC_SEC_ADDR  			0x02
#define RTCC_MIN_ADDR 			0x03
#define RTCC_HR_ADDR 			0x04
#define RTCC_DAY_ADDR 			0x05
#define RTCC_WEEKDAY_ADDR		0x06
#define RTCC_MONTH_ADDR 		0x07
#define RTCC_YEAR_ADDR 			0x08
#define RTCC_ALRM_MIN_ADDR 	    0x09
#define RTCC_ALRM_HR_ADDR 	    0x0A
#define RTCC_ALRM_DAY_ADDR 	    0x0B
#define RTCC_ALRM_WEEKDAY_ADDR 	    0x0C
#define RTCC_CLKOUT_ADDR 	    0x0D
#define RTCC_TIMERCTRL_ADDR 	        0x0E

/* setting the alarm flag to 0 enables the alarm.
 * set it to 1 to disable the alarm for that value.
 */
#define RTCC_ALARM				0x80
#define RTCC_ALARM_AIE 			0x02
#define RTCC_ALARM_AF 			0x08 // 0x08 : not 0x04!!!!
/* optional val for no alarm setting */
#define RTCC_NO_ALARM				99

#define RTCC_CENTURY_MASK 	0x80

/* date format flags */
#define RTCC_DATE_WORLD			0x01
#define RTCC_DATE_ASIA			0x02
#define RTCC_DATE_US				0x04
/* time format flags */
#define RTCC_TIME_HMS				0x01
#define RTCC_TIME_HM				0x02

/* square wave contants */
#define SQW_DISABLE     B(00000000)
#define SQW_32KHZ       B(10000000)
#define SQW_1024HZ      B(10000001)
#define SQW_32HZ        B(10000010)
#define SQW_1HZ         B(10000011)


/* time variables */
// byte hour;
// byte minute;
// byte sec;
// byte day;
// byte weekday;
// byte month;
// byte year;
// /* alarm */
// byte alarm_hour;
// byte alarm_minute;
// byte alarm_weekday;
// byte alarm_day;
// /* support */
// byte status1;
// byte status2;
// byte century;

char strOut[9];
char strDate[11];

unsigned char sec;
unsigned char minute;
unsigned char hour;

// int Rtcc_Addr;


/* arduino class */
// Rtc_Pcf8563();

void initClock();		/* zero out all values, disable all alarms */
void clearStatus();	/* set both status bytes to zero */

void getDate();			/* get date vals to local vars */
// void setDate(byte day, byte weekday, byte month, byte century, byte year);
void getTime();    /* get time vars + 2 status bytes to local vars */
void getAlarm();
void setTime(char sec, char minute, char hour);
// byte readStatus2();
bool alarmEnabled();
bool alarmActive();

void enableAlarm(); /* activate alarm flag and interrupt */
// void setAlarm(byte min, byte hour, byte day, byte weekday); /* set alarm vals, 99=ignore */
void clearAlarm();	/* clear alarm flag and interrupt */
void resetAlarm();  /* clear alarm flag but leave interrupt unchanged */
// void setSquareWave(byte frequency);
// void clearSquareWave();

unsigned char getSecond();
unsigned char getMinute();
unsigned char getHour();
// byte getDay();
// byte getMonth();
// byte getYear();
// byte getWeekday();
// byte getStatus1();
// byte getStatus2();

// byte getAlarmMinute();
// byte getAlarmHour();
// byte getAlarmDay();
// byte getAlarmWeekday();

		/*get a output string, these call getTime/getDate for latest vals */
// char *formatTime(byte style=RTCC_TIME_HMS);
		/* date supports 3 styles as listed in the wikipedia page about world date/time. */
// char *formatDate(byte style=RTCC_DATE_US);

// char *version();
		/* methods */
// byte decToBcd(byte value);
// byte bcdToDec(byte value);
