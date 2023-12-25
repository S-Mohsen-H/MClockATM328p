#ifndef TWOWIRE_H
#define TWOWIRE_H

#include "General.h"

extern void I2C_init();
extern uint8_t I2C_startTransmission(uint8_t SLA, uint8_t Rw);

extern uint8_t I2C_writeByte(uint8_t byte);

extern uint8_t I2C_writeStr(char *str);

extern uint8_t I2C_readByte(uint8_t *dataBuf, uint8_t ack);

extern uint8_t I2C_stopTransmission();

#endif