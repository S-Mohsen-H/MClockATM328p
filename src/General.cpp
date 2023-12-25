#include "General.h"

// void *operator new(size_t size)
// {
//     return malloc(size);
// }
// void operator delete(void *ptr)
// {
//     free(ptr);
// }

void nothing()
{
}

// ISR(USART_RX_vect)
// {
// }
uint8_t reverseBits(uint8_t num)
{
  // uint8_t arr[8];
  uint8_t rNum = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    // arr[i] = num & (1 << i);
    if (num & (1 << i))
      rNum |= 1 << (7 - i);
  }
  return rNum;
  // return (num & (1 << 7)) >> 7 |
  //        (num & (1 << 6)) >> 5 |
  //        (num & (1 << 5)) >> 3 |
  //        (num & (1 << 4)) >> 4 |
  //        (num & (1 << 3)) >> 3 |
  //        (num & (1 << 2)) >> 2 |
  //        (num & (1 << 1)) >> 1 |
  //        (num & (1 << 0)) >>
  //     ;
}

void blink(uint8_t time)
{
  PORTB |= 1;
  _delay_ms(time);
  PORTB &= ~(1);
}
void delay_ms_noINT(double ms)
{
  cli();
  _delay_ms(ms);
  // sei();
}
void delay_ms_INT(double ms)
{
  sei();
  _delay_ms(ms);
}