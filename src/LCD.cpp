#include "LCD.h"

void LCD_writeStr(char *str)
{
  while (*str != 0x00)
    LCD_writeByte((*(str++)), DATA);
}

void LCD_writeStr(uint8_t x, uint8_t y, char *str)
{
  LCD_setCo(x, y);
  LCD_writeStr(str);
}
void LCD_writeStr(uint8_t x,
                  uint8_t y,
                  const char *fmt, ...)
{
  // determine required buffer size
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  if (len < 0)
    return;

  // format message
  char *msg = NULL;
  msg = (char *)malloc(len + 1);
  va_start(args, fmt);
  vsnprintf(msg, len + 1, fmt, args);
  va_end(args);
  LCD_writeStr(x, y, msg);
  free(msg);
}

void LCD_init(void)
{
  delay(1000);
  LCD_writeByte(0x02, COMMAND);       // return home
  LCD_writeByte(0b00101100, COMMAND); // Function set
  LCD_writeByte(0x0F, COMMAND);
}

void LCD_writeByte(uint8_t command,
                   uint8_t Dc)
{
  uint8_t rCommand = reverseBits(command);
  _delay_us(1500);

  CLK_SR_SRCLR();
  SPI_writeByte((rCommand & 0x0F) | (1 << EN) |
                (Dc << RS));
  CLK_SR_RCLK();

  _delay_us(1500);

  CLK_SR_SRCLR();
  SPI_writeByte(((rCommand & 0x0F) & (~(1 << EN))) |
                (Dc << RS));
  CLK_SR_RCLK();

  _delay_us(1500);

  CLK_SR_SRCLR();
  SPI_writeByte(rCommand >> 4 | (1 << EN) |
                (Dc << RS));
  CLK_SR_RCLK();

  _delay_us(1500);

  CLK_SR_SRCLR();
  SPI_writeByte((rCommand >> 4 & (~(1 << EN))) |
                (Dc << RS));
  CLK_SR_RCLK();
}

// void LCD_writeByte(uint8_t *command, uint8_t *Dc)
// {
//   delay(2);
//   SPI_writeByte((*command) >> 4 | (1 << EN) | ((*Dc) << RS));
//   delay(2);
//   SPI_writeByte((*command) >> 4 & ~(1 << EN) | ((*Dc) << RS));
//   delay(2);
//   SPI_writeByte((*command) | (1 << EN) | ((*Dc) << RS));
//   delay(2);
//   SPI_writeByte((*command) & ~(1 << EN) | ((*Dc) << RS));
// }