#ifndef UART_H
#define UART_H
#include "General.h"

extern void UART_init();

// extern void UART_writeByte(uint8_t byte);

// extern void UART_writeByte(char byte);

extern int UART_writeStr(char *str,int size);

// extern uint8_t USART_ReceiveByte();

extern int UART_writeByte(char byte, FILE *stream);
extern int UART_readByte(FILE *stream);
// void usart_initialize(void);
// FILE uart_io = FDEV_SETUP_STREAM(UART_writeByte, UART_readByte, _FDEV_SETUP_RW); // c++ doesn't support this
extern FILE uart_io;

#endif