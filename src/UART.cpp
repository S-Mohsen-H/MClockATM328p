#include "UART.h"

FILE uart_io;

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
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0H = 0;
    UBRR0L = 51;
    uart_io.put = UART_sendByte;
    uart_io.get = UART_ReceiveByte;
    uart_io.flags = _FDEV_SETUP_RW;
    stdout = stdin = &uart_io;
}
// void UART_sendByte(uint8_t byte)
// {
//     while (!(UCSR0A & (1 << UDRE0)))
//         ;
//     UDR0 = byte;
// }
// void UART_sendByte(char byte)
// {
//     UART_sendByte((uint8_t)byte);
// }
void UART_sendStr(char *str)
{
    printf(str);
}
// uint8_t UART_ReceiveByte()
// {
//     while (!(UCSR0A & (1 << RXC0)))
//         ;
//     return UDR0;
// }
int UART_ReceiveByte(FILE *stream);
int UART_sendByte(char byte, FILE *stream)
{
    if (byte == '\n')
    {
        UART_sendByte('\r', stream);
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = byte;
    return 1;
}

int UART_ReceiveByte(FILE *stream)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}