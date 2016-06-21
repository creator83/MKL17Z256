#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "spi.h"

tact frq;
const char CS=9;
const char SCK=11;
const char MOSI=16;
const char MISO=17;


//Tact port A
Gpio spi_pin (Gpio::B);

void spi1_transmit (uint8_t data);
void spi1_init ();

int main()
{
	spi1_init ();

  while (1)
  {

	  	//spi_pin.clearPin(CS);
	  	spi1_transmit (0x0F);
		//spi_pin.setPin(CS);
		delay_ms (1000);
		//spi_pin.clearPin(CS);
		spi1_transmit (0xF0);
		//spi_pin.setPin(CS);
		delay_ms (1000);
  }
}

void spi1_init ()
{
	SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;

}

void spi1_transmit (uint8_t data)
{

}

