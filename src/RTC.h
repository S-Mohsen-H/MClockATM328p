#ifndef RTC_H
#define RTC_H
#include "General.h"

#define DS1307_ADDRESS 0b1101000

#define DS1307_SECOND 0
#define DS1307_MINUTE 1
#define DS1307_HOUR 2
#define DS1307_WEEKDAY 3
#define DS1307_MONTHDAY 4
#define DS1307_MONTH 5
#define DS1307_YEAR 6

#define bcdToBin(bcd) (((bcd >> 4) * 10) + (bcd & 0xF))
#define binToBcd(bin) ((bin % 10) | ((bin / 10) << 4))

typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t weekDay;
    char *weekDayStr;
    uint8_t monthDay;
    uint8_t month;
    uint16_t year16;
    uint8_t year;
} time_t;

extern uint8_t RTC_setTime(uint8_t second,
                           uint8_t minute,
                           uint8_t hour,
                           uint8_t weekDay,
                           uint8_t monthDay,
                           uint8_t month,
                           uint8_t year);
extern uint8_t RTC_setTime(time_t time);

extern uint8_t RTC_getTime(uint8_t *data);
extern uint8_t RTC_getTime(time_t *pTime);
extern void readTime(time_t *time, uint8_t sla);
extern void readTime2(uint8_t *timeArr, uint8_t sla);

extern void RTC_printTime(uint8_t *data);
#endif