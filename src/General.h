#ifndef GENERAL_H
#define GENERAL_H
#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "util/twi.h"
#include "SPI.h"
#include "TWI.h"
#include "LCD.h"
#include "UART.h"
#include "RTC.h"
#include "avr/interrupt.h"
#define setCo(x, y) (y ? 0xC0 + x : 0x80 + x)
#define byte_t uint8_t
// void * operator new(size_t size);
// void operator delete(void * ptr);
extern void nothing();
extern uint8_t reverseBits(uint8_t num);

// extern uint8_t bcdToBin(uint8_t bcd);

extern void blink(uint8_t time);

extern void delay_ms_noINT(double ms);
extern void delay_ms_INT(double ms);

#endif