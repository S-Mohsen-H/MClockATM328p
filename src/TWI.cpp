#include "TWI.h"
#include "avr/io.h"
#define TWI_STATUS (TWSR & 0b11111000)

void I2C_init()
{
  // F_CPU = 100000 * (16 + 2 * TWBR);
  TWBR = (cpuF - 1600000) / 200000;
  TWSR = 0;
  TWCR = 1 << TWEA | 1 << TWEN | 1 << TWIE;
}
uint8_t I2C_startTransmission(uint8_t SLA, uint8_t Rw)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
  if (TWI_STATUS == TW_START)
  {
    TWDR = (SLA << 1) | Rw;
    TWCR = 1 << TWINT | 1 << TWEN;
    while (!(TWCR & (1 << TWINT)))
      ;
    if (TW_STATUS == TW_MT_SLA_ACK)
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
uint8_t I2C_writeByte(uint8_t byte)
{
  TWDR = byte;
  TWCR |= 1 << TWINT | _BV(TWEN);
  while (!(TWCR & 1 << TWINT))
    ;
  if (TW_STATUS == TW_MT_DATA_ACK)
    return 1;
  else
    return 0;
}
uint8_t I2C_writeStr(char *str)
{
  while (*str)
  {
    if (!I2C_writeByte(*str))
      return 0;
    str++;
  }
  return I2C_writeByte('\0');
}
uint8_t I2C_readByte(uint8_t *dataBuf, uint8_t ack)
{
  if (ack)
  {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // generate ACK ?
    while (!(TWCR & (1 << TWINT)))
      ;
    if (TW_STATUS == TW_MR_DATA_ACK)
      *dataBuf = 5;
    else
      return TWDR;
  }
  else
  {
    TWCR = (1 << TWEN) | (1 << TWINT); // don't generate ACK
    while (!(TWCR & (1 << TWINT)))
      ;
    if (TW_STATUS == TW_MR_DATA_NACK)
      *dataBuf = 5;
    else
      return TWDR;
  }
  return 1;
  // for (uint8_t i = 0; i < size - 2; i++)
  // {
  //   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // generate ACK
  //   while (!(TWCR & (1 << TWINT)))
  //     ;
  //   if (TW_STATUS == TW_MR_DATA_ACK)
  //     dataBuf[i] = TWDR;
  //   else
  //     return 0;
  // }
  // TWCR = (1 << TWEN) | (1 << TWINT); // don't generate ACK
  // while (!(TWCR & (1 << TWINT)))
  //   ;
  // if (TW_STATUS == TW_MR_DATA_NACK)
  // {
  //   dataBuf[size - 1] = TWDR;
  //   return 1;
  // }
  // else
  //   return 0;
}
uint8_t I2C_stopTransmission()
{
  // TWCR |= 1 << TWINT | 1 << TWSTO;
  TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); // generate stop condition
  while (TWCR & (1 << TWSTO))
    ;
  return TW_STATUS;
}
