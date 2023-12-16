#include "RTC.h"
#include "General.h"
void RTC_setTime(uint8_t second,
                 uint8_t minute,
                 uint8_t hour,
                 uint8_t weekDay,
                 uint8_t monthDay,
                 uint8_t month,
                 uint8_t year)
{
    I2C_startTransmission(RTC_ADDRESS, TW_WRITE);
    I2C_transmit(0);
    I2C_transmit(second);
    I2C_transmit(minute);
    I2C_transmit(hour);
    I2C_transmit(weekDay);
    I2C_transmit(monthDay);
    I2C_transmit(month);
    I2C_transmit(year);
    I2C_stopTransmission();
}
void RTC_getTime(uint8_t *data)
{
    I2C_startTransmission(RTC_ADDRESS, TW_WRITE);
    I2C_transmit(0);
    I2C_stopTransmission();
    I2C_startTransmission(RTC_ADDRESS, TW_READ);
    for (uint8_t i = 0; i < 6; i++)
    {
        I2C_receive(data + i, 1);
    }
    I2C_receive(data + 6, 0);
    I2C_stopTransmission();
}
void RTC_printTime(uint8_t *data)
{
    char *dow = "DAY";
    switch (*(data + DS1307_WEEKDAY))
    {
    case 0:
        strcpy(dow, "SAT");
        // dow = (char *)"SAT";
        break;
    case 1:
        strcpy(dow, "SUN");
        // dow = (char *)"SUN";
        break;
    case 2:
        strcpy(dow, "MON");
        // dow = (char *)"MON";
        break;
    case 3:
        strcpy(dow, "TUE");
        // dow = (char *)"TUE";
        break;
    case 4:
        strcpy(dow, "WED");
        // dow = (char *)"WED";
        break;
    case 5:
        strcpy(dow, "THU");
        // dow = (char *)"THU";
        break;
    case 6:
        strcpy(dow, "FRI");
        // dow = (char *)"FRI";
        break;
    default:
        break;
    }
    printf("Date: %s 14%2d/%2d/%2d - Time: %2d:%2d:%2d\r", dow, *(data + DS1307_YEAR), *(data + DS1307_MONTH), *(data + DS1307_MONTHDAY), *(data + DS1307_HOUR), *(data + DS1307_MINUTE), *(data + DS1307_SECOND));
    // free(dow);
    // printf("hehvvvve\r");
}