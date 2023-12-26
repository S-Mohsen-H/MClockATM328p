#include "General.h"
time_t alarm1;
char str[2][17];
uint8_t buttonStates = 0;
typedef struct
{
  char data[0x400];
  byte_t lengthBuffer[4];
  uint16_t length;
} message_t;
typedef enum
{
  sGreet,
  sIdle,
  sShowData,
  sUpdateTime,
  sUpdateLocation,
  sText
} state_t;
state_t cState = sGreet;
int main(void)
{
  SPI_init();
  SPI_writeByte(0);
  _delay_ms(1000);
  LCD_init();
  LCD_writeByte(COMMAND_CLEAR, COMMAND);
  LCD_writeStr((char *)"hello", setCo(0, 0));
  I2C_init();
  message_t espMsg;
  while (1)
  {
    switch (cState)
    {
    case sGreet:
      LCD_writeStr((char *)"Hello", setCo(5, 0));
      LCD_writeStr((char *)"This is a test string", setCo(0, 1));
      _delay_ms(2000);
      cState = sUpdateTime;
      break;
    case sUpdateTime:
    {
      I2C_startTransmission(ESP32_SLA, TW_WRITE);
      I2C_writeByte(ESP32_COMMAND_WIFI_STATUS);
      I2C_stopTransmission();
      I2C_startTransmission(ESP32_SLA, TW_READ);
      I2C_readByte((uint8_t *)espMsg.data, 0);
      I2C_stopTransmission();
      LCD_writeStr((char *)"not connected", 0, 1);
      do
      {

        _delay_ms(2000);
      } while (espMsg.data[0] != WL_CONNECTED);
      LCD_writeStr((char *)"connected", 0, 1);

      // else
      // {
      I2C_startTransmission(ESP32_SLA, TW_WRITE);
      I2C_writeByte(ESP32_COMMAND_TIME);
      I2C_stopTransmission();
      I2C_startTransmission(ESP32_SLA, TW_READ);
      I2C_readByte((uint8_t *)espMsg.data, 1);
      I2C_readByte((uint8_t *)espMsg.data + 1, 0);
      espMsg.length = espMsg.data[0] << 8 | espMsg.data[1];

      for (uint16_t i = 0; i < espMsg.length - 1; i++)
        I2C_readByte((uint8_t *)espMsg.data + i, 1);
      I2C_readByte((uint8_t *)espMsg.data + espMsg.length - 1, 0);
      I2C_stopTransmission();
      cState = sShowData;
      // char *index;
      // char dasta[3333];
      // espMsg.data =strstr((char *)(espMsg.data), "\"datetime\"");
      strcpy(espMsg.data, strstr((char *)(espMsg.data), "\"datetime\""));
      // time_t cTime;
      // sscanf(index + 10, "%4d-%2d-%2dT%2d:%2d:%2d",
      //        &(cTime.year),
      //        &(cTime.month),
      //        &(cTime.monthDay),
      //        &(cTime.hour),
      //        &(cTime.minute),
      //        &(cTime.second));
      // index = strstr(index, "\"day_of_week\"");
      // (index + 13, "%1d", &(cTime.weekDay));
      // sprintf(str, "%2d-%d-%dT%d:%d:%d,%d",
      //         cTime.year,
      //         cTime.month,
      //         cTime.monthDay,
      //         cTime.hour,
      //         cTime.minute,
      //         cTime.second,
      //         cTime.weekDay);
      // LCD_writeStr(str, 0, 1);
      // }
      // _delay_ms(5000);
    }
    break;
    case sUpdateLocation:
      LCD_writeStr((char *)"Hello", setCo(5, 0));
      LCD_writeStr((char *)"Location", setCo(0, 1));
      _delay_ms(2000);
      cState = sGreet;
      break;
    case sShowData:
      char str[17];
      sprintf(str, "%d", espMsg.length);
      LCD_writeStr(str, 10, 0);
      LCD_writeStr((char *)(espMsg.data), 0, 1);
      cState = sIdle;
    case sIdle:
      _delay_ms(1000);
    default:
      break;
    }
  }
}