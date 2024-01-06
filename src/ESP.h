#ifndef ESP32_H
#define ESP32_H
#include "General.h"

// #define ESP32_SLA 0b1001001
#define ESP32_COMMAND_WIFI_STATUS 0xA0
#define ESP32_COMMAND_TIME 0xA1
#define ESP32_COMMAND_LOCATION 0xA2
#define ESP32_COMMAND_BT 0xB0

extern uint8_t ESP_getTime(time_t *pTime);
extern uint8_t ESP_getLocation(char *str);
extern char *btMessage;
extern uint8_t ESP_writeCommand(uint8_t command);
// extern uint8_t ESP_getStr(char *str, uint16_t size);

#endif