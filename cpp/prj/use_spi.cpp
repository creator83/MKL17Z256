#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"

tact frq;
const char CS=4;
const char SCK=5;
const char MOSI=6;
const char MISO=7;

//Tact port C
gpio spi_pin (gpio::C);

void spi0_transmit (uint8_t data);
void spi0_init ();

int main()
{
	//TPM0->CONTROLS[0].CnSC = 0;
	spi0_init ();

  while (1)
  {
	  	spi0_transmit (0x0F);
		delay_ms (1000);
		spi0_transmit (0xF0);
		delay_ms (1000);
  }
}

void spi0_init ()
{

	//Settings pins SCK, MOSI, MISO as ALT2
	spi_pin.setOutPort((1 << CS|1 << SCK|1 << MOSI|1 << MISO), gpio::Alt2);

	//Turn on tacting SPI0
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//===Settings SPI0===//
	// div=32
	SPI0->BR |= SPI_BR_SPR(5);
	SPI0->C2 |= SPI_C2_MODFEN_MASK;
	SPI0->C1 |= SPI_C1_MSTR_MASK |SPI_C1_SSOE_MASK | SPI_C1_SPE_MASK ;

}

void spi0_transmit (uint8_t data)
{
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI0->DL = data;
}

