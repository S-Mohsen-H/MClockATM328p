#include "General.h"
time_t cTime;
time_t espTime;
time_t time0;
uint16_t nowS;
void setClock(uint32_t clock);
void readButtons();
void updateLCD();
char *location;
/////////////////////////////////////////////////reg1
uint8_t reg1;
#define READ_DS1307 0
#define UPDATE_TIME 1
#define UPDATE_LOCATION 2
#define UPDATE_LCD 3
#define READ_BUTTONS 4
#define LCD_ACTIVE 5
#define SENT_COMMAND 6
/////////////////////////////////////////////////
uint8_t mode;
#define MODE_TIME 1
#define MODE_LOCATION 2
#define MODE_BT 3

#define SLEEP_TIMEOUT 60 * 3
uint8_t buttonStates = 0;

int main(void)
{
  location = (char *)malloc(20);
  // clock_prescale_set((clock_div_t)(log2(F_CPU / 1000000) - 1));
  cpuF = F_CPU;
  SPI_init();
  SPI_writeByte(0);
  delay(1000);
  LCD_init();
  LCD_clear();
  LCD_writeStr(0, 0, (char *)"MClock v0.1");
  delay(1000);
  I2C_init();
  TCCR0A = 1 << WGM01;
  TCCR0B = 1 << CS02 | 1 << CS00;
  OCR0A = 124;
  TCNT0 = 0;
  TIMSK0 = 1 << OCF0A;
  TCCR1B |= 1 << CS12 | 1 << CS11 | 1 << CS10 | 1 << WGM12;
  OCR1AH = 0x7F;
  OCR1AL = 0xFF;
  TIMSK1 = 1 << OCF1A;
  uint64_t nowMS = clockMS;
  nowS = clockS;
  while (1)
  {
    if (nowS - clockS > SLEEP_TIMEOUT)
    {
      cli();
      clearBit(PORTC, PC0);
      LCD_clear();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_bod_disable();
      sleep_enable();
      sleep_cpu();
      sleep_disable();
      setBit(PORTC, PC0);
      sei();
    }

    if (nowMS - clockMS > 200)
    {
      cli();
      updateLCD();
      nowMS = clockMS;
      sei();
    }
    if (reg1 & 1 << READ_DS1307)
    {
      cli();
      RTC_getTime(&cTime);
      clearBit(reg1, READ_DS1307);
      sei();
    }
    if (reg1 & 1 << READ_BUTTONS)
    {
      cli();
      readButtons();
      clearBit(reg1, READ_BUTTONS);
      sei();
    }
    if (reg1 & 1 << UPDATE_TIME)
    {
      cli();
      clearBit(reg1, UPDATE_TIME);
      ESP_getTime(&espTime);
      RTC_setTime(espTime);
      sei();
    }
    if (reg1 & 1 << UPDATE_LOCATION)
    {
      cli();
      clearBit(reg1, UPDATE_LOCATION);
      ESP_getLocation(location);
      sei();
    }
  }
}
ISR(TIMER0_COMPA_vect)
{
  cli();
  static uint8_t nowMS;
  nowMS = clockMS++;
  if (nowMS - clockMS > 200)
  {
    setBit(reg1, READ_BUTTONS);
    if (mode != MODE_BT)
      setBit(reg1, READ_DS1307);
    nowMS = clockMS;
  }
  sei();
}

ISR(TIMER1_COMPA_vect)
{
  cli();
  static uint16_t nowS;
  nowS = clockS++;
  if (nowS - clockS > 60)
  {
    nowS = clockS;
    if (mode != MODE_BT)
    {
      setBit(reg1, UPDATE_LOCATION);
      setBit(reg1, UPDATE_TIME);
    }
  }
}
ISR(TWI_vect)
{
  if (TW_STATUS == TW_SR_DATA_ACK)
  {
    cli();
    char *str = (char *)malloc(2);
    str[0] = (char)TWDR;
    str[1] = 0;
    strcat(btMessage, str);
    sei();
  }
}
void updateLCD()
{
  switch (mode)
  {
  case MODE_TIME:
    LCD_clear();
    LCD_writeStr(1, 0, "%s 20%d/%d/%d", cTime.weekDayStr, cTime.year, cTime.month, cTime.monthDay);
    LCD_writeStr(6, 1, "%d:%d:%d", cTime.hour, cTime.minute, cTime.second);
    break;
  case MODE_LOCATION:
    LCD_clear();
    LCD_writeStr(1, 0, location);
    break;
  case MODE_BT:
    LCD_clear();
    if (strlen(btMessage) > 16)
      LCD_writeStr(0, 0, btMessage + strlen(btMessage) - 16);
  default:
    break;
  }
}

void readButtons()
{
  buttonStates = (PIND & (1 << SW1)) |
                 ((PIND & (1 << SW2)) << 1) |
                 ((PIND & (1 << SW3)) << 2);
  switch (buttonStates)
  {
  case 1:
    cli();
    mode = MODE_TIME;
    nowS = clockS;
    clearBit(TWCR, TWIE);
    ESP_writeCommand(ESP32_COMMAND_TIME);
    sei();
    break;
  case 1 << 1:
    cli();
    mode = MODE_LOCATION;
    nowS = clockS;
    clearBit(TWCR, TWIE);
    ESP_writeCommand(ESP32_COMMAND_LOCATION);
    sei();
    break;
  case 1 << 2:
    cli();
    mode = MODE_BT;
    nowS = clockS;
    setBit(TWCR, TWIE);
    ESP_writeCommand(ESP32_COMMAND_BT);
    sei();
    break;
  default:
    break;
  }
}
void setClock(uint32_t clock)
{
  if (clock == 8000000 && F_CPU == 8000000)
  {
    cpuF = clock;
  }
  else if (clock == 8000000 && F_CPU == 16000000)
  {
    clock_prescale_set(clock_div_2);
    cpuF = clock;
  }
  else if (clock == 2000000 && F_CPU == 16000000)
  {
    clock_prescale_set(clock_div_8);
    cpuF = clock;
  }
  else if (clock == 2000000 && F_CPU == 8000000)
  {
    clock_prescale_set(clock_div_4);
    cpuF = clock;
  }
  else
    cpuF = F_CPU;
}