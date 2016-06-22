#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "spi.h"

tact frq;
/*
const char CS=9;
const char SCK=11;
const char MOSI=16;
const char MISO=17;


//Tact port A
Gpio spi_pin (Gpio::B);

void spi1_transmit (uint8_t data);
void spi1_init ();*/

int main()
{
	spi spi0;

  while (1)
  {
	  spi0.transmit_8(0x0F);
	  delay_ms(1000);
	  spi0.transmit_8(0xF0);
	  delay_ms(1000);

  }
}

