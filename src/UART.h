#ifndef UART_H
#define UART_H
#include "General.h"

extern void UART_init();

// extern void UART_sendByte(uint8_t byte);

// extern void UART_sendByte(char byte);

extern int UART_sendStr(char *str,int size);

// extern uint8_t USART_ReceiveByte();

extern int UART_sendByte(char byte, FILE *stream);
extern int UART_ReceiveByte(FILE *stream);
// void usart_initialize(void);
// FILE uart_io = FDEV_SETUP_STREAM(UART_sendByte, UART_ReceiveByte, _FDEV_SETUP_RW); // c++ doesn't support this
extern FILE uart_io;

#endif