#include "LCD.h"

void LCD_writeStr(char *str, uint8_t coordination)
{
  delay(1);
  // str += String(format);
  // strcat(str, format);
  if (coordination != NOCHANGE)
    LCD_writeByte(coordination, COMMAND);
  while (*str != 0x00)
  {
    LCD_writeByte((*str), DATA);
    str++;
  }
}
void LCD_writeStr(char *str, uint8_t x, uint8_t y)
{
  LCD_writeStr(str, setCo(x, y));
}
void LCD_writeStr(uint8_t x, uint8_t y, const char *fmt, ...)
{
  // determine required buffer size
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  if (len < 0)
    return;

  // format message
  // char msg[len + 1]; // or use heap allocation if implementation doesn't support VLAs
  char *msg = NULL;
  msg = (char *)malloc(len + 1);
  va_start(args, fmt);
  vsnprintf(msg, len + 1, fmt, args);
  va_end(args);
  LCD_writeStr(msg, x, y);
  free(msg);
}

void LCD_init(void)
{
  delay(1000);

  // LCD_writeByte(0x01, COMMAND); // clear
  LCD_writeByte(0x02, COMMAND); // return home

  // uint8_t rCommand = reverseBits(0x02);
  // delay(2);
  // SPI_writeByte((rCommand & 0x0F) | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte(((rCommand & 0x0F) & (~(1 << EN))) | (0 << RS));
  // delay(2);
  // SPI_writeByte(rCommand >> 4 | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte((rCommand >> 4 & (~(1 << EN))) | (0 << RS));

  LCD_writeByte(0b00101100, COMMAND); // Function set
  //  rCommand = reverseBits(0b00101100);
  // delay(2);
  // SPI_writeByte((rCommand & 0x0F) | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte(((rCommand & 0x0F) & (~(1 << EN))) | (0 << RS));
  // delay(2);
  // SPI_writeByte(rCommand >> 4 | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte((rCommand >> 4 & (~(1 << EN))) | (0 << RS));
  // LCD_writeByte(0b101, COMMAND);                            // return home
  // LCD_writeByte(makeByte((uint8_t *)"00001111"), COMMAND); // on/off
  // LCD_writeByte(0b00001111, COMMAND); // on/off
  // LCD_writeByte2(makeByte((uint8_t *)"00101000")); //
  LCD_writeByte(0x0F, COMMAND);
  //  rCommand = reverseBits(0x0F);
  // delay(2);
  // SPI_writeByte((rCommand & 0x0F) | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte(((rCommand & 0x0F) & (~(1 << EN))) | (0 << RS));
  // delay(2);
  // SPI_writeByte(rCommand >> 4 | (1 << EN) | (0 << RS));
  // delay(2);
  // SPI_writeByte((rCommand >> 4 & (~(1 << EN))) | (0 << RS));
  // LCD_writeByte(0x0C, COMMAND);
}

void LCD_writeByte(uint8_t command, uint8_t DATcom)
{
  // delay(2);
  // SPI_writeByte((command >> 4) | (1 << EN) | (DATcom << RS));
  // delay(2);
  // SPI_writeByte(((command >> 4) & (~(1 << EN))) | (DATcom << RS));
  // delay(2);
  // SPI_writeByte(command | (1 << EN) | (DATcom << RS));
  // delay(2);
  // SPI_writeByte((command & (~(1 << EN))) | (DATcom << RS));
  uint8_t rCommand = reverseBits(command);
  _delay_us(1500);
  SPI_writeByte((rCommand & 0x0F) | (1 << EN) | (DATcom << RS));
  _delay_us(1500);
  SPI_writeByte(((rCommand & 0x0F) & (~(1 << EN))) | (DATcom << RS));
  _delay_us(1500);
  SPI_writeByte(rCommand >> 4 | (1 << EN) | (DATcom << RS));
  _delay_us(1500);
  SPI_writeByte((rCommand >> 4 & (~(1 << EN))) | (DATcom << RS));
}

// void LCD_writeByte(uint8_t *command, uint8_t *DATcom)
// {
//   delay(2);
//   SPI_writeByte((*command) >> 4 | (1 << EN) | ((*DATcom) << RS));
//   delay(2);
//   SPI_writeByte((*command) >> 4 & ~(1 << EN) | ((*DATcom) << RS));
//   delay(2);
//   SPI_writeByte((*command) | (1 << EN) | ((*DATcom) << RS));
//   delay(2);
//   SPI_writeByte((*command) & ~(1 << EN) | ((*DATcom) << RS));
// }