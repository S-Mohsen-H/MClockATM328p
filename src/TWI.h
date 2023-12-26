#ifndef TWOWIRE_H
#define TWOWIRE_H

#include "General.h"
#define ESP32_SLA 0b1001001
#define ESP32_COMMAND_WIFI_STATUS 0xA0
#define ESP32_COMMAND_TIME 0xA1
#define ESP32_COMMAND_LOCATION 0xA2

extern void I2C_init();
extern uint8_t I2C_startTransmission(uint8_t SLA, uint8_t Rw);

extern uint8_t I2C_writeByte(uint8_t byte);

extern uint8_t I2C_writeStr(char *str);

extern uint8_t I2C_readByte(uint8_t *dataBuf, uint8_t ack);

extern uint8_t I2C_stopTransmission();

#endif