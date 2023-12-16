#ifndef LCD_H
#define LCD_H

#include "General.h"

#define COMMAND_CLEAR 0x01
#define NOCHANGE 0xFF

#define RS 6
#define EN 4
#define RW 5

#define DATA 1
#define COMMAND 0

extern void LCD_printStr(char *str, uint8_t coordination);
extern void LCD_sendByte(uint8_t command, uint8_t DATcom);
extern void LCD_init(void);

#endif