#include "RTC.h"
#include "General.h"
#ifdef __AVR_ATmega328P__
#define if_I2C_startTransmission(X, Y)    \
    do                                    \
    {                                     \
        if (!I2C_startTransmission(X, Y)) \
            return 0;                     \
    } while (0);
#define if_I2C_writeByte(X)    \
    do                         \
    {                          \
        if (!I2C_writeByte(X)) \
            return 0;          \
    } while (0);
#define if_I2C_readByte(X, Y)    \
    do                           \
    {                            \
        if (!I2C_readByte(X, Y)) \
            return 0;            \
    } while (0);
#define if_I2C_stopTransmission()    \
    do                               \
    {                                \
        if (!I2C_stopTransmission()) \
            return 0;                \
    } while (0);
uint8_t RTC_setTime(uint8_t second,
                    uint8_t minute,
                    uint8_t hour,
                    uint8_t weekDay,
                    uint8_t monthDay,
                    uint8_t month,
                    uint8_t year)
{
    if_I2C_startTransmission(DS1307_ADDRESS, TW_WRITE);
    if_I2C_writeByte(0);
    if_I2C_writeByte(second);
    if_I2C_writeByte(minute);
    if_I2C_writeByte(hour);
    if_I2C_writeByte(weekDay);
    if_I2C_writeByte(monthDay);
    if_I2C_writeByte(month);
    if_I2C_writeByte(year);
    return (I2C_stopTransmission());
}
uint8_t RTC_setTime(time_t time)
{
    return (RTC_setTime(time.second, time.minute, time.hour, time.weekDay, time.monthDay, time.month, time.year));
}
uint8_t RTC_getTime(uint8_t *data)
{
    if_I2C_startTransmission(DS1307_ADDRESS, TW_WRITE);
    if_I2C_writeByte(0);
    if_I2C_stopTransmission();
    if_I2C_startTransmission(DS1307_ADDRESS, TW_READ);
    for (uint8_t i = 0; i < 6; i++)
        if_I2C_readByte(data + i, 1);
    if_I2C_readByte(data + 6, 0);
    if_I2C_stopTransmission();
}
uint8_t RTC_getTime(time_t *pTime)
{
    if_I2C_startTransmission(DS1307_ADDRESS, TW_WRITE);
    if_I2C_writeByte(0);
    if_I2C_stopTransmission();
    if_I2C_startTransmission(DS1307_ADDRESS, TW_READ);
    if_I2C_readByte(&(pTime->second), 1);
    if_I2C_readByte(&(pTime->minute), 1);
    if_I2C_readByte(&(pTime->hour), 1);
    if_I2C_readByte(&(pTime->weekDay), 1);
    if_I2C_readByte(&(pTime->monthDay), 1);
    if_I2C_readByte(&(pTime->month), 1);
    if_I2C_readByte(&(pTime->year), 0);
    return (I2C_stopTransmission());
}
// void readTime(time_t *time, uint8_t sla)
// {
//     if (sla == DS1307_ADDRESS)
// {
//     I2C_startTransmission(DS1307_ADDRESS, TW_WRITE);
//     I2C_writeByte(0);
//     I2C_stopTransmission();
//     I2C_startTransmission(DS1307_ADDRESS, TW_READ);
//     I2C_readByte(&(time->second), 1);
//     I2C_readByte(&(time->minute), 1);
//     I2C_readByte(&(time->hour), 1);
//     I2C_readByte(&(time->weekDay), 1);
//     I2C_readByte(&(time->monthDay), 1);
//     I2C_readByte(&(time->month), 1);
//     I2C_readByte(&(time->year), 0);
//     I2C_stopTransmission();
// }
//     else if (sla == ESP32_SLA)
//     {
//         I2C_startTransmission(ESP32_SLA, TW_WRITE);
//         I2C_writeByte(0xA1);
//         I2C_stopTransmission();
//         I2C_startTransmission(ESP32_SLA, TW_READ);
//         I2C_readByte(&(time->second), 1);
//         I2C_readByte(&(time->minute), 1);
//         I2C_readByte(&(time->hour), 1);
//         I2C_readByte(&(time->weekDay), 1);
//         I2C_readByte(&(time->monthDay), 1);
//         I2C_readByte(&(time->month), 1);
//         I2C_readByte(&(time->year), 0);
//         I2C_stopTransmission();
//     }
// }
void readTime2(uint8_t *timeArr, uint8_t sla)
{
    if (sla == DS1307_ADDRESS)
    {
        I2C_startTransmission(DS1307_ADDRESS, TW_WRITE);
        I2C_writeByte(0);
        I2C_stopTransmission();
        I2C_startTransmission(DS1307_ADDRESS, TW_READ);
        I2C_readByte(&(timeArr[0]), 1);
        I2C_readByte(&(timeArr[1]), 1);
        I2C_readByte(&(timeArr[2]), 1);
        I2C_readByte(&(timeArr[3]), 1);
        I2C_readByte(&(timeArr[4]), 1);
        I2C_readByte(&(timeArr[5]), 1);
        I2C_readByte(&(timeArr[6]), 0);
        I2C_stopTransmission();
    }
    else if (sla == ESP32_SLA)
    {
        I2C_startTransmission(ESP32_SLA, TW_WRITE);
        I2C_writeByte(0xA3);
        I2C_stopTransmission();
        I2C_startTransmission(ESP32_SLA, TW_READ);
        I2C_readByte(&(timeArr[0]), 1);
        I2C_readByte(&(timeArr[1]), 1);
        I2C_readByte(&(timeArr[2]), 1);
        I2C_readByte(&(timeArr[3]), 1);
        I2C_readByte(&(timeArr[4]), 1);
        I2C_readByte(&(timeArr[5]), 1);
        I2C_readByte(&(timeArr[6]), 0);
        // I2C_readByte(timeArr + 0, 1);
        // I2C_readByte(timeArr + 1, 1);
        // I2C_readByte(timeArr + 2, 1);
        // I2C_readByte(timeArr + 3, 1);
        // I2C_readByte(timeArr + 4, 1);
        // I2C_readByte(timeArr + 5, 1);
        // I2C_readByte(timeArr + 6, 0);
        I2C_stopTransmission();
        // I2C_startTransmission(ESP32_SLA, TW_WRITE);
        // I2C_writeByte(2);
        // I2C_stopTransmission();
        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // for (uint8_t i = 0; i < 100; i++)
        // {
        //     I2C_readByte(timeArr + i, 1);
        //     if (timeArr[i] == 0)
        //     {
        //         I2C_readByte(timeArr + i + 1, 0);
        //         break;
        //     }
        // }
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[1]), 0);
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[2]), 0);
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[3]), 0);
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[4]), 0);
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[5]), 0);
        // I2C_stopTransmission();

        // I2C_startTransmission(ESP32_SLA, TW_READ);
        // I2C_readByte(&(timeArr[6]), 0);
        // I2C_stopTransmission();
    }
}
void RTC_printTime(uint8_t *data)
{
    char *dow = (char *)"DAY";
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
}
#endif
