#include "UART.h"

void UART_init()
{
    FILE uart_io;

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
    uart_io.put = UART_writeByte;
    uart_io.get = UART_readByte;
    uart_io.flags = _FDEV_SETUP_RW;
    stdout = stdin = &uart_io;
}
// void UART_writeByte(uint8_t byte)
// {
//     while (!(UCSR0A & (1 << UDRE0)))
//         ;
//     UDR0 = byte;
// }
// void UART_writeByte(char byte)
// {
//     UART_writeByte((uint8_t)byte);
// }
int UART_writeStr(char *str, int size)
{
    // printf(str);
    for (uint8_t i = 0; i < size; i++)
    {
        UART_writeByte(*(str + i), NULL);
    }
    return 1;
}
// uint8_t UART_readByte()
// {
//     while (!(UCSR0A & (1 << RXC0)))
//         ;
//     return UDR0;
// }
int UART_readByte(FILE *stream);
int UART_writeByte(char byte, FILE *stream)
{
    if (byte == '\n')
    {
        UART_writeByte('\r', stream);
        UART_writeByte('\n', stream);
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = byte;
    return 1;
}

int UART_readByte(FILE *stream)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}