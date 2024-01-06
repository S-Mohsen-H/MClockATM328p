#include "I2C.h"
#include "avr/io.h"
#define TWI_STATUS (TWSR & 0b11111000)
uint16_t timeOutMS;
uint64_t tick;

void I2C_setTimeOut(uint16_t timeOutMS_)
{
  timeOutMS = timeOutMS_;
}

void I2C_init()
{
  // cpuF = 100000 * (16 + 2 * TWBR);
  TWBR = (cpuF - 1600000) / 200000;
  TWSR = 0;
  TWCR = 1 << TWEA | 1 << TWEN | 1 << TWIE;
}
uint8_t I2C_startTransmission(uint8_t SLA, uint8_t Rw)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  tick = 0;
  uint64_t nowMS = clockMS;
  while (!(TWCR & (1 << TWINT)))
  {
    if (clockMS - nowMS > timeOutMS)
    {
      // setBit(eReg, ERROR_I2C);
      return 0;
    }
  }
  if (TWI_STATUS != TW_START)
    return 0;

  TWDR = (SLA << 1) | Rw;
  TWCR = 1 << TWINT | 1 << TWEN;
  nowMS = clockMS;
  while (!(TWCR & (1 << TWINT)))
  {
    if (clockMS - nowMS > timeOutMS)
    {
      // setBit(eReg, ERROR_I2C);
      return 0;
    }
  }
  if (TW_STATUS == TW_MT_SLA_ACK)
    return 1;
  else
    return 0;
}
uint8_t I2C_writeByte(uint8_t byte)
{
  uint64_t tick;
  TWDR = byte;
  TWCR |= 1 << TWINT | _BV(TWEN);
  uint64_t nowMS = clockMS;
  while (!(TWCR & 1 << TWINT))
  {
    if (clockMS - nowMS > timeOutMS)
    {
      // setBit(eReg, ERROR_I2C);
      return 0;
    }
  }
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
  uint64_t nowMS;

  if (ack)
  {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // generate ACK ?
    nowMS = clockMS;
    while (!(TWCR & (1 << TWINT)))
    {
      if (clockMS - nowMS > timeOutMS)
      {
        // setBit(eReg, ERROR_I2C);
        return 0;
      }
    }
    if (TW_STATUS == TW_MR_DATA_ACK)
      *dataBuf = TWDR;
    else
      return 0;
  }
  else
  {
    TWCR = (1 << TWEN) | (1 << TWINT); // don't generate ACK
    nowMS = clockMS;
    while (!(TWCR & (1 << TWINT)))
    {
      if (clockMS - nowMS > timeOutMS)
      {
        // setBit(eReg, ERROR_I2C);
        return 0;
      }
    }
    if (TW_STATUS == TW_MR_DATA_NACK)
      *dataBuf = TWDR;
    else
      return 0;
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
  uint64_t nowMS = clockMS;
  while (TWCR & (1 << TWSTO))
  {
    if (clockMS - nowMS > timeOutMS)
    {
      // setBit(eReg, ERROR_I2C);
      return 0;
    }
  }
  return 1;
}

uint8_t I2C_readStr(uint8_t *str, uint16_t size)
{
  for (uint16_t i = 0; i < size; i++)
  {
    if (!I2C_readByte(str + i, 1))
      return 0;
    if (*(str + i) == 0)
    {
      if (!I2C_readByte(str + i + 1, 0))
        return 0;
      return 1;
    }
  }
  return 0;
}