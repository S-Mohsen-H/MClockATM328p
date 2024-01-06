#ifndef UART_H
#define UART_H
#include "General.h"
extern FILE uart_io;

extern void UART_init();
extern int UART_writeStr(char *str, int size);
extern int UART_writeByte(char byte, FILE *stream);
extern int UART_readByte(FILE *stream);

#endif