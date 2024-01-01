// #include "General.h"
// #include "json_decoder.h"
// // #include "jsmn.h"
// // #include "ArduinoJson.h"
// void updateLCD();

// // char *dummy = "{\"abbreviation\":\"+0330\",\"client_ip\":\"217.218.49.158\",\"datetime\":\"2023-12-22T22:06:09.504615+03:30\",\"day_of_week\":5,\"day_of_year\":356,\"dst\":false,\"dst_from\":null,\"dst_offset\":0,\"dst_until\":null,\"raw_offset\":12600,\"timezone\":\"Asia/Tehran\",\"unixtime\":1703270169,\"utc_datetime\":\"2023-12-22T18:36:09.504615+00:00\",\"utc_offset\":\"+03:30\",\"week_number\":51}";
// // #include "avr/io.h"
// // #include "avr/delay.h"
// // #include "SPI.h"
// // #include "LCD.h"
// // uint8_t f = 0;

// // int main()
// // {
// //   DDRD = 0;
// //   // PORTD = 1 << SW1;
// //   // PORTD = 1 << SW1 | 1 << SW2 | 1 << SW3;
// //   // DDRC = 1 << LED_YELLOW;
// //   // DDRC = 0xFF;
// //   DDRB |= 1 << LED_BLUE;
// //   // DDRB = 1 << PB5;
// //   // DDRC = 1 << PC0;
// //   SPI_init();
// //   SPI_writeByte(0);
// //   delay(1000);
// //   LCD_init();
// //   LCD_writeByte(COMMAND_CLEAR, COMMAND);
// //   LCD_writeStr((char *)"hello", setCo(0, 0));
// //   // PCMSK2 = 1 << PCINT23;
// //   // PCICR = 1 << PCIE2;
// //   // uint8_t f = 0;
// //   char str[2];
// //   // SMCR = 1 << SM1;
// //   // SMCR |= 1 << SE;
// //   // delay(1000);
// //   // sei();
// //   // sleep_cpu();
// //   // // sleep_enable();
// //   // sleep_bod_disable();
// //   // sleep_disable();
// //   // LCD_writeByte(COMMAND_CLEAR, COMMAND);
// //   while (1)
// //   {
// //     // PORTB |= 1 << PB5;
// //     delay(2000);
// //     PORTB |= 1 << LED_BLUE;
// //     delay(2000);
// //     PORTB &= ~(1 << LED_BLUE);
// //     // PORTB &= ~(1 << PB5);
// //     // if ((PIND & (1 << SW1)) != 0)
// //     //   // PORTB = 1 << LED_BLUE;
// //     //   PORTB = 1 << PB5;
// //     // else
// //     //   PORTB = 0;
// //     //   LCD_writeStr("low", 0, 0);
// //     // else
// //     //   LCD_writeStr("high", 0, 0);
// //     // cli();
// //     // sprintf(str, "%d", f);
// //     // LCD_writeStr(str, 0, 1);
// //     // sei();
// //     // f = !f;
// //     // cli();
// //     // if (f)
// //     //   LCD_writeStr("high", 0, 1);
// //     // else
// //     //   LCD_writeStr("low", 0, 1);
// //     // sei();
// //     // delay(100);
// //   }
// // }
// // // ISR(PCINT2_vect)
// // // {
// // //   if ((PIND & (1 << SW1)) == 0)
// // //   {
// // //     cli();
// // //     // LCD_writeStr("low", 1, 5);
// // //     if (f)
// // //     {
// // //       PORTC |= 1 << LED_BLUE;
// // //     }
// // //     // LCD_writeStr("low", 5, 0);
// // //     else
// // //     {
// // //       PORTC &= ~(1 << LED_BLUE);
// // //     }
// // //     f = !f;
// // //     sei();
// // //   }

// // //   // else
// // //   // LCD_writeStr("high", 1, 5);

// // //   // LCD_writeStr("high", 10, 0);
// // // }
// time_t alarm1;
// time_t cTime;
// time_t espTime;
// time_t time0;
// byte_t timeArr[14];
// uint8_t reg1;
// #define READ_DS1307 0
// #define UPDATE_ESP 1
// // #define UPDATE_LOCATION 2
// #define UPDATE_LCD 3
// #define READ_BUTTONS 4
// #define LCD_ACTIVE 5

// // #define READ_BUTTONS (reg1 & (1 << 4))
// void setClock(uint32_t clock)
// {
//   if (clock == 8000000 && F_CPU == 8000000)
//   {
//     cpuF = clock;
//   }
//   else if (clock == 8000000 && F_CPU == 16000000)
//   {
//     clock_prescale_set(clock_div_2);
//     cpuF = clock;
//   }
//   else if (clock == 2000000 && F_CPU == 16000000)
//   {
//     clock_prescale_set(clock_div_8);
//     cpuF = clock;
//   }
//   else if (clock == 2000000 && F_CPU == 8000000)
//   {
//     clock_prescale_set(clock_div_4);
//     cpuF = clock;
//   }
//   else
//     cpuF = F_CPU;
// }
// char str[2][17];
// uint8_t buttonStates = 0;
// typedef struct
// {
//   char data[0x400];
//   byte_t lengthBuffer[4];
//   uint16_t length;
// } message_t;
// typedef enum
// {
//   sGreet,
//   sIdle,
//   sShowTime,
//   sUpdateTime,
//   sUpdateLocation,
//   sText
// } state_t;
// state_t cState = sGreet;
// int main(void)
// {
//   time0.second = 0;
//   time0.minute = 0;
//   time0.hour = 0;
//   time0.month = 0;
//   time0.weekDay = 0;
//   time0.year = 0;
//   time0.year16 = 0;
//   // clock_prescale_set((clock_div_t)(log2(F_CPU / 1000000) - 1));
//   cpuF = F_CPU;
//   SPI_init();
//   SPI_writeByte(0);
//   delay(1000);
//   LCD_init();
//   LCD_writeByte(COMMAND_CLEAR, COMMAND);
//   LCD_writeStr((char *)"hello", setCo(0, 0));
//   I2C_init();
//   uint8_t sec;
//   // RTC_setTime(1, 2, 3, 4, 5, 6, 7);
//   // I2C_startTransmission(RTC_ADDRESS, TW_WRITE);
//   // I2C_readByte(&sec, 0);
//   // I2C_startTransmission(RTC_ADDRESS, TW_READ);
//   // I2C_writeByte(sec & (0xFF >> 1));
//   // I2C_stopTransmission();
//   TCCR0A = 1 << WGM01;
//   TCCR0B = 1 << CS02 | 1 << CS00;
//   OCR0A = 195;
//   OCR0B = 97;
//   TCNT0 = 0;
//   TIMSK0 = 1 << OCF0A | 1 << OCF0B;
//   TCCR1B |= 1 << CS12 | 1 << CS10 | 1 << WGM12;
//   OCR1AH = (byte_t)((cpuF / 512) >> 8);
//   OCR1AL = (byte_t)(cpuF / 512);
//   OCR1BH = (byte_t)((cpuF / 1024) >> 8);
//   OCR1BL = (byte_t)(cpuF / 1024);
//   // OCR1A = 0x3D07;

//   TCNT1H = 0;
//   TCNT1L = 0;
//   TIMSK1 = 1 << OCF1A | 1 << OCF1B;
//   message_t espMsg;
//   char *data;
//   data = (char *)malloc(0x200 * sizeof(char));
//   char *chTime;
//   chTime = (char *)malloc(42 * sizeof(char));
//   sei();
//   while (1)
//   {
//     // cli();
//     if (reg1 & 1 << READ_DS1307)
//     {
//       cli();
//       // readTime2(&cTime, RTC_ADDRESS);
//       clearBit(reg1, READ_DS1307);
//       sei();
//     }
//     if (reg1 & 1 << UPDATE_LCD)
//     {
//       cli();
//       updateLCD();
//       clearBit(reg1, UPDATE_LCD);
//       sei();
//     }
//     if (reg1 & 1 << UPDATE_ESP)
//     {
//       uint8_t i = 0;
//       uint16_t length = 22;
//       cli();
//       clearBit(reg1, UPDATE_ESP);
//       readTime2(timeArr, ESP32_SLA);
//       // I2C_startTransmission(ESP32_SLA, TW_WRITE);
//       // I2C_writeByte(12);
//       // I2C_stopTransmission();
//       // I2C_startTransmission(ESP32_SLA, TW_READ);
//       // for (uint8_t i = 0; i < 100; i++)
//       // {
//       //   I2C_readByte(timeArr + i, 1);
//       //   if (timeArr[i] == 0)
//       //   {
//       //     I2C_readByte(timeArr + i + 1, 0);
//       //     break;
//       //   }
//       // }
//       // I2C_stopTransmission();
//       // 2023-12-29T18:48:34.774511+03:30
//       sei();
//     }

//     // cTime = time0;
//     sei();
//     delay(1);
//     // switch (cState)
//     // {
//     // case sGreet:
//     //   LCD_writeStr((char *)"Hello", setCo(5, 0));
//     //   LCD_writeStr((char *)"This is a test string", setCo(0, 1));
//     //   delay(2000);
//     //   cState = sShowTime;
//     //   break;
//     // case sShowTime:
//     //   cli();
//     //   I2C_startTransmission(RTC_ADDRESS, TW_WRITE);
//     //   I2C_writeByte(0);
//     //   I2C_stopTransmission();
//     //   I2C_startTransmission(RTC_ADDRESS, TW_READ);
//     //   I2C_readByte(&(cTime.second), 1);
//     //   I2C_readByte(&(cTime.minute), 1);
//     //   I2C_readByte(&(cTime.hour), 1);
//     //   I2C_readByte(&(cTime.weekDay), 1);
//     //   I2C_readByte(&(cTime.monthDay), 1);
//     //   I2C_readByte(&(cTime.month), 1);
//     //   I2C_readByte(&(cTime.year), 0);
//     //   I2C_stopTransmission();
//     //   sprintf(str[0], "%d:%d:%d", bcdToBin(cTime.hour), bcdToBin(cTime.minute), bcdToBin(cTime.second));
//     //   LCD_writeStr(str[0], 0, 0);
//     //   sei();
//     //   delay(1000);
//     //   break;
//     // case sUpdateTime:
//     // {
//     //   I2C_startTransmission(ESP32_SLA, TW_WRITE);
//     //   I2C_writeByte(ESP32_COMMAND_WIFI_STATUS);
//     //   I2C_stopTransmission();
//     //   I2C_startTransmission(ESP32_SLA, TW_READ);
//     //   I2C_readByte((uint8_t *)espMsg.data, 0);
//     //   I2C_stopTransmission();
//     //   LCD_writeStr((char *)"not connected", 0, 1);
//     //   do
//     //   {

//     //     delay(2000);
//     //   } while (espMsg.data[0] != WL_CONNECTED);
//     //   LCD_writeStr((char *)"connected", 0, 1);

//     //   // else
//     //   // {
//     //   I2C_startTransmission(ESP32_SLA, TW_WRITE);
//     //   I2C_writeByte(ESP32_COMMAND_TIME);
//     //   I2C_stopTransmission();
//     //   I2C_startTransmission(ESP32_SLA, TW_READ);
//     //   I2C_readByte((uint8_t *)espMsg.data, 1);
//     //   I2C_readByte((uint8_t *)espMsg.data + 1, 0);
//     //   espMsg.length = espMsg.data[0] << 8 | espMsg.data[1];

//     //   for (uint16_t i = 0; i < espMsg.length - 1; i++)
//     //     I2C_readByte((uint8_t *)espMsg.data + i, 1);
//     //   I2C_readByte((uint8_t *)espMsg.data + espMsg.length - 1, 0);
//     //   I2C_stopTransmission();
//     //   cState = sShowTime;
//     //   // char *index;
//     //   // char dasta[3333];
//     //   // espMsg.data =strstr((char *)(espMsg.data), "\"datetime\"");
//     //   strcpy(espMsg.data, strstr((char *)(espMsg.data), "\"datetime\""));
//     //   // time_t cTime;
//     //   // sscanf(index + 10, "%4d-%2d-%2dT%2d:%2d:%2d",
//     //   //        &(cTime.year),
//     //   //        &(cTime.month),
//     //   //        &(cTime.monthDay),
//     //   //        &(cTime.hour),
//     //   //        &(cTime.minute),
//     //   //        &(cTime.second));
//     //   // index = strstr(index, "\"day_of_week\"");
//     //   // (index + 13, "%1d", &(cTime.weekDay));
//     //   // sprintf(str, "%2d-%d-%dT%d:%d:%d,%d",
//     //   //         cTime.year,
//     //   //         cTime.month,
//     //   //         cTime.monthDay,
//     //   //         cTime.hour,
//     //   //         cTime.minute,
//     //   //         cTime.second,
//     //   //         cTime.weekDay);
//     //   // LCD_writeStr(str, 0, 1);
//     //   // }
//     //   // delay(5000);
//     // }
//     // break;
//     // case sUpdateLocation:
//     //   LCD_writeStr((char *)"Hello", setCo(5, 0));
//     //   LCD_writeStr((char *)"Location", setCo(0, 1));
//     //   delay(2000);
//     //   cState = sGreet;
//     //   break;
//     // // case sShowTime:
//     // //   char str[17];
//     // //   sprintf(str, "%d", espMsg.length);
//     // //   LCD_writeStr(str, 10, 0);
//     // //   LCD_writeStr((char *)(espMsg.data), 0, 1);
//     // //   cState = sIdle;
//     // case sIdle:
//     //   delay(1000);
//     // default:
//     //   break;
//     // }
//   }
// }
// uint8_t Dt = 0;
// void updateLCD()
// {
//   sprintf(str[0], "%d:%d:%d", bcdToBin(cTime.hour), bcdToBin(cTime.minute), bcdToBin(cTime.second));
//   // sprintf(str[1], "%u:%u:%u", espTime.hour, espTime.minute, espTime.second);
//   if (Dt)
//   {
//     sprintf(str[1], "%u:%u:%u",
//             timeArr[2],
//             timeArr[1],
//             timeArr[0]);
//   }
//   else
//   {
//     sprintf(str[1], "%u-%u-%u-%u",
//             timeArr[6],
//             timeArr[5],
//             timeArr[4],
//             timeArr[3]);
//   }
//   LCD_writeStr(str[0], 1, 0);
//   LCD_writeStr(str[1], 1, 1);

//   // LCD_writeStr((char *)timeArr, 1, 1);
//   // LCD_writeStr(1, 1, "%u:%u:%u", timeArr[2], timeArr[1], timeArr[0]);
// }

// uint8_t aliveFlag = 0;
// ISR(TIMER1_COMPA_vect)
// // ISR(TIMER1_OVF_vect)
// {
//   cli();
//   setBit(reg1, UPDATE_ESP);
//   Dt = !Dt;
//   LCD_CLEAR();
//   sei();
// }
// ISR(TIMER0_COMPA_vect)
// {
//   cli();
//   setBit(reg1, UPDATE_LCD);
//   sei();
// }
// ISR(TIMER0_COMPB_vect)
// {
//   cli();
//   setBit(reg1, READ_DS1307);
//   sei();
// }
// ISR(TIMER1_COMPB_vect)
// {
//   cli();
//   aliveFlag = !aliveFlag;
//   sprintf(str[1], "%d", aliveFlag);
//   LCD_writeStr(str[1], 0, 1);
//   sei();
// }
// // #include "General.h"
// // int main(void)
// // {
// //   cpuF = F_CPU;
// //   SPI_init();
// //   SPI_writeByte(0);
// //   delay(1000);
// //   LCD_init();
// //   LCD_writeByte(COMMAND_CLEAR, COMMAND);
// //   LCD_writeStr((char *)"hello", setCo(0, 0));
// //   I2C_init();
// //   char data[0x200];
// //   while (1)
// //   {
// //     _delay_ms(1000);
// //     uint8_t i = 0;
// //     uint16_t length = 22;
// //     // cli();
// //     // clearBit(reg1, UPDATE_ESP);
// //     I2C_startTransmission(ESP32_SLA, TW_WRITE);
// //     I2C_writeByte(0xA1);
// //     I2C_stopTransmission();
// //     I2C_startTransmission(ESP32_SLA, TW_READ);
// //     // I2C_readByte((uint8_t *)data, 1);
// //     for (; i < 34; i++)
// //     {
// //       // if (1)
// //       I2C_readByte((uint8_t *)(data + i), 1);
// //       if (!(*(data + i)))
// //       {
// //         I2C_readByte((uint8_t *)(data + i + 1), 0);
// //         break;
// //       }
// //     }
// //     // I2C_readByte((uint8_t *)(data + 34), 0);
// //     // // length = data[0] << 8 | data[1];
// //     // for (uint16_t l = 0; l < (length - 1); l++)
// //     //   I2C_readByte((uint8_t *)(data + l), 1);
// //     // I2C_readByte((uint8_t *)(data + length - 1), 0);
// //     I2C_stopTransmission();
// //     uint8_t year;
// //     // sscanf(data , "%d", &year);
// //     // LCD_writeStr(1, 1, "%d", year);
// //     LCD_writeStr(data, 1, 1);
// //     // StaticJsonDocument<128> doc1;
// //     // deserializeJson(doc1, data);
// //     // LCD_writeStr(doc1["datetime"], 1, 1);
// //     // LCD_writeStr(3, 1, "%d:%d:%d", bcdToBin(cTime.hour), bcdToBin(cTime.minute), bcdToBin(cTime.second));
// //     // sei();
// //   }
// // }
#include "General.h"
int main()
{
  SPI_init();
  SPI_writeByte(0);
  delay(500);
  LCD_init();
  LCD_writeStr("hello", 5, 0);
  I2C_init();
  char *str1 = "hello MF";
  uint8_t *str2 = (uint8_t *)malloc(100 * sizeof(char));
  while (1)
  {
    I2C_startTransmission(ESP32_SLA, TW_WRITE);
    for (int i = 0; i < strlen(str1); i++)
      I2C_writeByte(*(str1 + i));
    I2C_writeByte(0);
    I2C_stopTransmission();
    // I2C_startTransmission(ESP32_SLA, TW_READ);
    // for (uint8_t i = 0; i < 100; i++)
    // {
    //   I2C_readByte(str2 + i, 1);
    //   if (str2[i] == 0)
    //   {
    //     I2C_readByte(str2 + i + 1, 0);
    //     break;
    //   }
    // }
    // I2C_stopTransmission();
    LCD_writeStr((char *)str2, 0, 1);
    delay(1000);
  }
}