#include "General.h"
// #include "usart.h"
#include "avr/interrupt.h"
// int main()
// {
//   DDRB = 1 << PB0;
//   while (1)
//   {
//     PORTB = 1 << PB0;
//     _delay_ms(1000);
//     PORTB = 0;
//     _delay_ms(500);
//   }
// }
int main(void)
{
  sei();
  UART_init();
  SPI_init();
  SPI_sendByte(0);
  _delay_ms(1000);

  LCD_init();
  LCD_sendByte(COMMAND_CLEAR, COMMAND);

  // char str[17];
  LCD_printStr((char *)"hello", setCo(0, 0));
  LCD_printStr((char *)"hiiiiffffhfff", setCo(0, 1));
  // uint64_t i = 0;
  // while (1)
  // {
  //   // sprintf(str, "s= %i", i++);
  //   // LCD_printStr(str, setCo(0, 1));
  //   // printf("hello\n");
  //   // _delay_ms(1);
  //   // PORTB |= 1 << PB0;
  //   // _delay_ms(500);
  //   // PORTB &= ~(1 << PB0);
  //   // _delay_ms(1000);
  // }

  I2C_init();
  uint8_t data[100];
  // printf("\n\n");
  // while (1)
  // {
  //   RTC_getTime(data);
  //   for (uint8_t i = 0; i < 7; i++)
  //     data[i] = bcdToBin(data[i]);

  //   RTC_printTime(data);
  //   // LCD_printStr()
  //   _delay_ms(10);
  // };
  while (1)
  {
    I2C_startTransmission(0b1001001, TW_READ);
    // I2C_transmit('C');
    for (uint8_t i = 0; i < 99; i++)
    {
      I2C_receive(data + i, 1);
    }
    I2C_receive(data + 99, 0);
    // I2C_stopTransmission;
    // I2C_transmitString("hello ESP32!\n");
    I2C_stopTransmission();
    printf((char *)data);
    _delay_ms(1000);
  }

  // _delay_ms(15);
  // while (1)
  // {
  //   // if (I2C_startTransmission(0b11010000))
  //   if (I2C_startTransmission(0b11010000))
  //     LCD_printStr((char *)"1", setCo(0, 0));
  //   I2C_stopTransmission();
  //   if (I2C_startTransmission(0b11010001))
  //     LCD_printStr((char *)"2", setCo(0, 0));
  //   for (uint8_t i = 0; i < 6; i++)
  //   {
  //     I2C_receive(data + i, 1);
  //   }
  //   I2C_receive(data + 6, 0);
  //   I2C_stopTransmission();

  //   printf("%d\n", data[0]);
  //   _delay_ms(1000);
  //   // if (I2C_receive(data, 7))
  //   //   LCD_printStr((char *)"2", setCo(1, 0));
  //   // char *str2 = NULL;
  //   // str2 = (char *)malloc(100 * sizeof(char));
  //   // sprintf(str2, "helloThereESP32&");
  //   // for (uint8_t i = 0; i++; i < 100 && str2[i] != '&')
  //   //   if (I2C_transmit(str2[i]) == TW_MT_DATA_ACK)
  //   //     LCD_printStr((char *)"2", setCo(2, 0));

  //   // if (I2C_stopTransmission())
  //   //   LCD_printStr((char *)"3", setCo(2, 0));

  //   // blink(100);
  //   // // sprintf(str, "s:%d,m:%d,h:%d", data[0], data[1], data[2]);
  //   // LCD_sendByte(COMMAND_CLEAR, COMMAND);
  //   // LCD_printStr(str, setCo(0, 0));

  //   // _delay_ms(1000);
  // }
  // DDRD = 1 << PD7;
  // UART_init();
  // SREG |= 1 << SREG_I;
  // char *str3 = NULL;
  // str3 = (char *)malloc(20 * sizeof(uint8_t));
  // // strcpy(str3, "Hello PC\n");
  // I2C_init();
  // uint64_t j = 0;

  // while (1)
  // {
  //   if (I2C_startTransmission(0b11010000))
  //     UART_sendStr("started\n");
  //   if (I2C_transmit(0))
  //     UART_sendStr("transmitted 0\n");

  //   I2C_stopTransmission();
  //   UART_sendStr("stopped\n");

  //   if (I2C_startTransmission(0b11010000))
  //     UART_sendStr("started 2\n");
  //   if (I2C_receive(data, 7))
  //     UART_sendStr("received\n");

  //   I2C_stopTransmission();
  //   for (uint8_t i = 0; i < 7; i++)
  //   {
  //     sprintf(str3, "Register: %d = %d\r\n", i, data[i]);
  //     UART_sendStr(str3);
  //   }
  //   // if (a)
  //   //   PORTD &= ~(1 << PD7);
  //   // else
  //   //   PORTD |= 1 << PD7;
  //   // a = !a;
  //   // sprintf(str3, "%d\r\n", j++);
  //   // for (uint8_t i = 0; str3[i] != 0; i++)
  //   // {
  //   //   UART_sendByte(str3[i]);
  //   // }
  //   _delay_ms(1000);
  // }
}
// uint8_t a = 0;

ISR(USART_RX_vect)
{
  uint8_t dummy = UDR0;
}
// {
//   // if (a)
//   //   PORTD &= ~(1 << PD7);
//   // else
//   //   PORTD |= 1 << PD7;
//   // a = !a;
//   uint8_t dummy = UDR0;
//   LCD_sendByte(COMMAND_CLEAR, COMMAND);

//   switch (dummy)
//   {
//   case '0':
//     LCD_printStr((char*)"0000000000000", setCo(0, 0));
//     // PORTD &= ~(1 << PD7);
//     break;
//   case '1':
//     // PORTD |= 1 << PD7;
//     LCD_printStr((char*)"1111111111111", setCo(0, 1));
//   default:
//     break;
//   }
// }
// ISR(USART_TX_vect)
// {
//   if (a)
//     PORTD &= ~(1 << PD7);
//   else
//     PORTD |= 1 << PD7;
//   a = !a;
//   uint8_t dummy = UDR0;
//   // switch (UDR0)
//   // {
//   // case '0':
//   //   PORTD &= ~(1 << PD7);
//   //   break;
//   // case '1':
//   //   PORTD |= 1 << PD7;
//   // default:
//   //   break;
//   // }
// }
// ISR(USART_RX_vect)
// {
//   register uint8_t tmp_rx_Head = (rxn_Head + 1) & RXn_BUFFER_MASK;
//   register uint8_t tmp = UDRn_REGISTER;

//   if (rxn_Tail != tmp_rx_Head)
//   {
//     rxn_Head = tmp_rx_Head; // it would create race condition if not used in isr
//     rxn_buffer[tmp_rx_Head] = tmp;
//   }
// }
// ISR(TWI_vect)
// {
//   switch (TW_STATUS)
//   {
//   case TW_START:

//     break;
//   /** \ingroup util_twi
//       \def TW_REP_START
//       repeated start condition transmitted */
//   case TW_REP_START:
//     break;
//   /* Master Transmitter */
//   /** \ingroup util_twi
//       \def TW_MT_SLA_ACK
//       SLA+W transmitted, ACK received */
//   case TW_MT_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MT_SLA_NACK
//       SLA+W transmitted, NACK received */
//   case TW_MT_SLA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MT_DATA_ACK
//       data transmitted, ACK received */
//   case TW_MT_DATA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MT_DATA_NACK
//       data transmitted, NACK received */
//   case TW_MT_DATA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MT_ARB_LOST
//       arbitration lost in SLA+W or data */
//   case TW_MT_ARB_LOST:
//     break;
//   /* Master Receiver */
//   /** \ingroup util_twi
//       \def TW_MR_ARB_LOST
//       arbitration lost in SLA+R or NACK */

//   /** \ingroup util_twi
//       \def TW_MR_SLA_ACK
//       SLA+R transmitted, ACK received */
//   case TW_MR_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MR_SLA_NACK
//       SLA+R transmitted, NACK received */
//   case TW_MR_SLA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MR_DATA_ACK
//       data received, ACK returned */
//   case TW_MR_DATA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_MR_DATA_NACK
//       data received, NACK returned */
//   case TW_MR_DATA_NACK:
//     break;
//   /* Slave Transmitter */
//   /** \ingroup util_twi
//       \def TW_ST_SLA_ACK
//       SLA+R received, ACK returned */
//   case TW_ST_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_ST_ARB_LOST_SLA_ACK
//       arbitration lost in SLA+RW, SLA+R received, ACK returned */
//   case TW_ST_ARB_LOST_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_ST_DATA_ACK
//       data transmitted, ACK received */
//   case TW_ST_DATA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_ST_DATA_NACK
//       data transmitted, NACK received */
//   case TW_ST_DATA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_ST_LAST_DATA
//       last data byte transmitted, ACK received */
//   case TW_ST_LAST_DATA:
//     break;
//   /* Slave Receiver */
//   /** \ingroup util_twi
//       \def TW_SR_SLA_ACK
//       SLA+W received, ACK returned */
//   case TW_SR_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_ARB_LOST_SLA_ACK
//       arbitration lost in SLA+RW, SLA+W received, ACK returned */
//   case TW_SR_ARB_LOST_SLA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_GCALL_ACK
//       general call received, ACK returned */
//   case TW_SR_GCALL_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_ARB_LOST_GCALL_ACK
//       arbitration lost in SLA+RW, general call received, ACK returned */
//   case TW_SR_ARB_LOST_GCALL_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_DATA_ACK
//       data received, ACK returned */
//   case TW_SR_DATA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_DATA_NACK
//       data received, NACK returned */
//   case TW_SR_DATA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_GCALL_DATA_ACK
//       general call data received, ACK returned */
//   case TW_SR_GCALL_DATA_ACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_GCALL_DATA_NACK
//       general call data received, NACK returned */
//   case TW_SR_GCALL_DATA_NACK:
//     break;
//   /** \ingroup util_twi
//       \def TW_SR_STOP
//       stop or repeated start condition received while selected */
//   case TW_SR_STOP:
//     break;
//   /* Misc */
//   /** \ingroup util_twi
//       \def TW_NO_INFO
//       no state information available */
//   case TW_NO_INFO:
//     break;
//   /** \ingroup util_twi
//       \def TW_BUS_ERROR
//       illegal start or stop condition */
//   case TW_BUS_ERROR:
//     break;
//   default:
//     break;
//   }
// }
uint8_t slaRW;

// ISR(TWI_vect)
// {
//   switch (TW_STATUS)
//   {
//   // All Master
//   case TW_START:     // sent start condition
//   case TW_REP_START: // sent repeated start condition
//     // copy device address and r/w bit to output register and ack
//     TWDR = twi_slarw;
//     twi_reply(1);
//     break;

//   // Master Transmitter
//   case TW_MT_SLA_ACK:  // slave receiver acked address
//   case TW_MT_DATA_ACK: // slave receiver acked data
//     // if there is data to send, send it, otherwise stop
//     if (twi_masterBufferIndex < twi_masterBufferLength)
//     {
//       // copy data to output register and ack
//       TWDR = twi_masterBuffer[twi_masterBufferIndex++];
//       twi_reply(1);
//     }
//     else
//     {
//       if (twi_sendStop)
//       {
//         twi_stop();
//       }
//       else
//       {
//         twi_inRepStart = true; // we're gonna send the START
//         // don't enable the interrupt. We'll generate the start, but we
//         // avoid handling the interrupt until we're in the next transaction,
//         // at the point where we would normally issue the start.
//         TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
//         twi_state = TWI_READY;
//       }
//     }
//     break;
//   case TW_MT_SLA_NACK: // address sent, nack received
//     twi_error = TW_MT_SLA_NACK;
//     twi_stop();
//     break;
//   case TW_MT_DATA_NACK: // data sent, nack received
//     twi_error = TW_MT_DATA_NACK;
//     twi_stop();
//     break;
//   case TW_MT_ARB_LOST: // lost bus arbitration
//     twi_error = TW_MT_ARB_LOST;
//     twi_releaseBus();
//     break;

//   // Master Receiver
//   case TW_MR_DATA_ACK: // data received, ack sent
//     // put byte into buffer
//     twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
//     __attribute__((fallthrough));
//   case TW_MR_SLA_ACK: // address sent, ack received
//     // ack if more bytes are expected, otherwise nack
//     if (twi_masterBufferIndex < twi_masterBufferLength)
//     {
//       twi_reply(1);
//     }
//     else
//     {
//       twi_reply(0);
//     }
//     break;
//   case TW_MR_DATA_NACK: // data received, nack sent
//     // put final byte into buffer
//     twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
//     if (twi_sendStop)
//     {
//       twi_stop();
//     }
//     else
//     {
//       twi_inRepStart = true; // we're gonna send the START
//       // don't enable the interrupt. We'll generate the start, but we
//       // avoid handling the interrupt until we're in the next transaction,
//       // at the point where we would normally issue the start.
//       TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
//       twi_state = TWI_READY;
//     }
//     break;
//   case TW_MR_SLA_NACK: // address sent, nack received
//     twi_stop();
//     break;
//   // TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

//   // Slave Receiver
//   case TW_SR_SLA_ACK:            // addressed, returned ack
//   case TW_SR_GCALL_ACK:          // addressed generally, returned ack
//   case TW_SR_ARB_LOST_SLA_ACK:   // lost arbitration, returned ack
//   case TW_SR_ARB_LOST_GCALL_ACK: // lost arbitration, returned ack
//     // enter slave receiver mode
//     twi_state = TWI_SRX;
//     // indicate that rx buffer can be overwritten and ack
//     twi_rxBufferIndex = 0;
//     twi_reply(1);
//     break;
//   case TW_SR_DATA_ACK:       // data received, returned ack
//   case TW_SR_GCALL_DATA_ACK: // data received generally, returned ack
//     // if there is still room in the rx buffer
//     if (twi_rxBufferIndex < TWI_BUFFER_LENGTH)
//     {
//       // put byte in buffer and ack
//       twi_rxBuffer[twi_rxBufferIndex++] = TWDR;
//       twi_reply(1);
//     }
//     else
//     {
//       // otherwise nack
//       twi_reply(0);
//     }
//     break;
//   case TW_SR_STOP: // stop or repeated start condition received
//     // ack future responses and leave slave receiver state
//     twi_releaseBus();
//     // put a null char after data if there's room
//     if (twi_rxBufferIndex < TWI_BUFFER_LENGTH)
//     {
//       twi_rxBuffer[twi_rxBufferIndex] = '\0';
//     }
//     // callback to user defined callback
//     twi_onSlaveReceive(twi_rxBuffer, twi_rxBufferIndex);
//     // since we submit rx buffer to "wire" library, we can reset it
//     twi_rxBufferIndex = 0;
//     break;
//   case TW_SR_DATA_NACK:       // data received, returned nack
//   case TW_SR_GCALL_DATA_NACK: // data received generally, returned nack
//     // nack back at master
//     twi_reply(0);
//     break;

//   // Slave Transmitter
//   case TW_ST_SLA_ACK:          // addressed, returned ack
//   case TW_ST_ARB_LOST_SLA_ACK: // arbitration lost, returned ack
//     // enter slave transmitter mode
//     twi_state = TWI_STX;
//     // ready the tx buffer index for iteration
//     twi_txBufferIndex = 0;
//     // set tx buffer length to be zero, to verify if user changes it
//     twi_txBufferLength = 0;
//     // request for txBuffer to be filled and length to be set
//     // note: user must call twi_transmit(bytes, length) to do this
//     twi_onSlaveTransmit();
//     // if they didn't change buffer & length, initialize it
//     if (0 == twi_txBufferLength)
//     {
//       twi_txBufferLength = 1;
//       twi_txBuffer[0] = 0x00;
//     }
//     __attribute__((fallthrough));
//     // transmit first byte from buffer, fall
//   case TW_ST_DATA_ACK: // byte sent, ack returned
//     // copy data to output register
//     TWDR = twi_txBuffer[twi_txBufferIndex++];
//     // if there is more to send, ack, otherwise nack
//     if (twi_txBufferIndex < twi_txBufferLength)
//     {
//       twi_reply(1);
//     }
//     else
//     {
//       twi_reply(0);
//     }
//     break;
//   case TW_ST_DATA_NACK: // received nack, we are done
//   case TW_ST_LAST_DATA: // received ack, but we are done already!
//     // ack future responses
//     twi_reply(1);
//     // leave slave receiver state
//     twi_state = TWI_READY;
//     break;

//   // All
//   case TW_NO_INFO: // no state information
//     break;
//   case TW_BUS_ERROR: // bus error, illegal stop/start
//     twi_error = TW_BUS_ERROR;
//     twi_stop();
//     break;
//   }
// }
