#include "General.h"
alarm_t alarm1;
char str[2][17];

int main(void)
{
    SPI_init();
    SPI_writeByte(0);
    LCD_init();
}