#ifndef LCD_H
#define LCD_H

#include "General.h"

#define RS 6
#define EN 4
#define RW 5

#define DATA 1
#define COMMAND 0
#define NO_CO_CHANGE 0xFF
#define LCD_clear() LCD_writeByte(0x01, COMMAND)
// #define LCD_setCo(x, y) \
//     LCD_writeByte(y ? 0xC0 + x : 0x80 + x, COMMAND)

#define CLK_SR_SRCLR()             \
    do                             \
    {                              \
        PORTB &= ~(1 << SR_SRCLR); \
        PORTB |= (1 << SR_SRCLR);  \
    } while (0)
#define CLK_SR_RCLK()             \
    do                            \
    {                             \
        PORTB &= ~(1 << SR_RCLK); \
        PORTB |= (1 << SR_RCLK);  \
    } while (0)

extern void LCD_writeStr(uint8_t coordination, char *str);
extern void LCD_writeByte(uint8_t command, uint8_t Dc);
extern void LCD_init(void);
extern void LCD_writeStr(uint8_t x, uint8_t y, char *str);
extern void LCD_writeStr(uint8_t x, uint8_t y, const char *fmt, ...);
#endif