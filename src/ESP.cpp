#include "ESP.h"

uint8_t ESP_writeCommand(uint8_t command)
{
    if (!I2C_startTransmission(ESP32_SLA, TW_WRITE))
        return 0;
    if (!I2C_writeByte(command))
        return 0;
    return I2C_stopTransmission();
}
uint8_t ESP_getStr(char *str, uint16_t size)
{
    if (!I2C_startTransmission(ESP32_SLA, TW_READ))
        return 0;
    if (!I2C_readStr((uint8_t *)str, size))
        return 0;
    return I2C_stopTransmission();
}
uint8_t ESP_getTime(time_t *pTime)
{
    // 2023-12-29T18:48:34.774511+03:30
    char *str = NULL;
    str = (char *)malloc(50);
    if (!ESP_writeCommand(ESP32_COMMAND_TIME))
        return 0;
    if (!ESP_getStr(str, 50))
        return 0;
    sprintf(str, "%d-%d-%dT%d:%d:%d", &(pTime->year16), &(pTime->month), &(pTime->monthDay), &(pTime->hour), &(pTime->minute), &(pTime->second));
    return 1;
}
uint8_t ESP_getLocation(char *str)
{

    if (!ESP_writeCommand(ESP32_COMMAND_LOCATION))
        return 0;
    return ESP_getStr(str, 50);
}

uint8_t ESP_getMessage()
{
}
