#ifndef SPI_H
#define SPI_H
#include "General.h"


#define SR_RCLK PB1  // 12 -> D9
#define SR_SRCLR PB2 // 10 -> D10
#define SR_SER PB3   // 14 -> D11
#define SR_SRCLK PB5 // 11 -> D13

extern void SPI_writeByte(uint8_t value);

extern void SPI_init();


#endif