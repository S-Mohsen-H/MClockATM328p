#include "SPI.h"
void SPI_init()
{
  // Set SCK MOSI MISO and SS as output
  DDRB = (1 << SR_SRCLR) | (1 << SR_SER) | (1 << SR_RCLK) | (1 << SR_SRCLK);
  // SPI Control Register – SPCR
  //  Enable SPI, change data order and set to master mode
  SPCR = (1 << SPE) | (1 << DORD) | (1 << MSTR);
}
void SPI_writeByte(uint8_t value)
{

  // PORTB &= ~(1 << SR_SRCLR);
  // PORTB |= (1 << SR_SRCLR);

  SPDR = value; // write byte
  while (!(SPSR & (1 << SPIF)))
    ;

  // PORTB &= ~(1 << SR_RCLK);
  // PORTB |= (1 << SR_RCLK);
}