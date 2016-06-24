#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "spi.h"


tact frq;
const char CS=4;
const char SCK=5;
const char MOSI=6;
const char MISO=7;

//Tact port C
gpio spi_pin (gpio::C);



int main()
{
	spi spi_0 (spi::SPI_0, spi::C, spi::div32);

  while (1)
  {

	  spi_0.transmit_8(0xF0);
	  delay_ms (500);
	  spi_0.transmit_8(0x0F);
	  delay_ms (500);


  }
}


