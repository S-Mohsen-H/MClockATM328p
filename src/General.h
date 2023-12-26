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
#include "avr/sleep.h"

typedef enum {
    WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
    WL_IDLE_STATUS      = 0,
    WL_NO_SSID_AVAIL    = 1,
    WL_SCAN_COMPLETED   = 2,
    WL_CONNECTED        = 3,
    WL_CONNECT_FAILED   = 4,
    WL_CONNECTION_LOST  = 5,
    WL_DISCONNECTED     = 6
} wl_status_t;

#define LED_BLUE PB0
#define LED_YELLOW PC2
#define SW1 PD7 // PCINT23
#define SW2 PD5 // PCINT21
#define SW3 PD6 // PCINT22

#define setCo(x, y) (y ? 0xC0 + x : 0x80 + x)
#define byte_t uint8_t
// void * operator new(size_t size);
// void operator delete(void * ptr);
extern void nothing();
extern uint8_t reverseBits(uint8_t num);

// extern uint8_t bcdToBin(uint8_t bcd);

extern void blink(uint8_t time);

// extern void delay_ms_noINT(double ms);
// extern void delay_ms_INT(double ms);

#endif