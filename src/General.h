#ifndef GENERAL_H
#define GENERAL_H
#define __DELAY_BACKWARD_COMPATIBLE__
#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "util/twi.h"
#include "avr/power.h"
#include "avr/interrupt.h"
#include "avr/sleep.h"
#include "SPI.h"
#include "LCD.h"
#include "ESP.h"
#ifdef __AVR_ATmega328P__
#include "I2C.h"
#include "UART.h"
#include "RTC.h"
#endif
typedef enum
{
    WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL = 1,
    WL_SCAN_COMPLETED = 2,
    WL_CONNECTED = 3,
    WL_CONNECT_FAILED = 4,
    WL_CONNECTION_LOST = 5,
    WL_DISCONNECTED = 6
} wl_status_t;
#define setBit(reg, bit) \
    do                   \
    {                    \
        reg |= 1 << bit; \
    } while (0)
#define clearBit(reg, bit)  \
    do                      \
    {                       \
        reg &= ~(1 << bit); \
    } while (0)
#define LED_BLUE PB0
#define LED_YELLOW PC2
#define SW1 PD7 // PCINT23
#define SW2 PD5 // PCINT21
#define SW3 PD6 // PCINT22

#define setCo(x, y) (y ? 0xC0 + x : 0x80 + x)
#define LCD_setCo(x, y) LCD_writeByte(y ? 0xC0 + x : 0x80 + x, COMMAND)

#define ESP32_SLA 0b1001001

typedef uint8_t byte_t;
uint8_t eReg;
#define ERROR_I2C 1
// #define F_CPU__ 2000000
// void * operator new(size_t size);
// void operator delete(void * ptr);
extern void nothing();
extern uint8_t reverseBits(uint8_t num);
extern uint64_t cpuF;
// extern uint8_t bcdToBin(uint8_t bcd);
extern void delay(double ms);

extern void blink(uint8_t time);

// extern void delay_ms_noINT(double ms);
// extern void delay_ms_INT(double ms);
// extern
extern int log2(int num);
extern char *strPtr(char *str);
extern uint64_t clockMS;
extern uint32_t clockS;

// extern uint16_t nowMS;

#endif