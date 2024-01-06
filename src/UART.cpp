#include "UART.h"
#ifdef __AVR_ATmega328P__

#ifdef _STDIO_H_
FILE uart_io;
#endif

void UART_init()
{

    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART0 Mode: Asynchronous
    // USART Baud Rate: 38400 (Double Speed Mode)
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0) | (0 << TXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << UPM01);
    UBRR0H = 0;
    UBRR0L = 51;
#ifdef _STDIO_H_
    uart_io.put = UART_writeByte;
    uart_io.get = UART_readByte;
    uart_io.flags = _FDEV_SETUP_RW;
    stdout = stdin = &uart_io;
#endif
}
int UART_writeStr(char *str, int size)
{
#ifdef _STDIO_H_
    printf(str);
#else

    for (uint8_t i = 0; i < size; i++)
    {
        UART_writeByte(*(str + i), NULL);
    }
    return 1;
#endif
}

int UART_readByte(FILE *stream)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}
int UART_writeByte(char byte, FILE *stream)
{
    // #ifdef _STDIO_H_
    //     if (byte == '\n')
    //     {
    //         UART_writeByte('\r', stream);
    //         UART_writeByte('\n', stream);
    //     }
    // #endif
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = byte;
    return 1;
}

#endif