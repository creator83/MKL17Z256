#include "spi.h"

//CS,SCK,MISO,MOSI
uint8_t spi::pins_d[2][4]={{4,5,6,7},{6,3,4,5}};

PotMemFn spi::ptr_receive[2] = {};

PotMemF spi::ptr_transmite[2] = {};
ptr_ex spi::ptr_exchange[2] =  {};

spi::spi()
:pin (gpio::C)
{
  
  //===Settings pins===//

  //Settings pins SCK, MOSI, MISO as ALT2
  	pin.setOutPort((1 << CS|1 << SCK|1 << MOSI|1 << MISO), gpio::Alt2);
  
  
  //===Settings SPI===//
  //Turn on tacting SPI0
  SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

  //===Settings SPI0===//
  // div=32
  SPI0->BR |= SPI_BR_SPR(5);
  SPI0->C2 |= SPI_C2_MODFEN_MASK;
  SPI0->C1 |= SPI_C1_MSTR_MASK |SPI_C1_SSOE_MASK | SPI_C1_SPE_MASK ;

}


void spi::transmit_8 (uint16_t data)
{
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI0->DL = data;
}

void spi::transmit_16 (uint16_t data)
{

}

void spi::transmit (uint16_t data)
{
	(this->*(spi::ptr_transmite[size_]))(data);
}

uint16_t spi::receive_8 ()
{
}

uint16_t spi::receive_16 ()
{

}

uint16_t spi::receive ()
{
	 return (this->*(spi::ptr_receive[size_]))();
}


uint16_t spi::exchange_8 (uint16_t data)
{

}
uint16_t spi::exchange_16 (uint16_t data)
{

}
uint16_t spi::exchange (uint16_t data)
{
	return (this->*(spi::ptr_exchange[size_]))(data);
}

