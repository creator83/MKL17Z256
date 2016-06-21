#include "spi.h"
#include "MKL17Z4.h"

//CS,SCK,MISO,MOSI

uint8_t spi::pins_d[2][4]={{4,5,6,7},{6,3,4,5}};

PotMemFn spi::ptr_receive[2] = {&spi::receive_8, &spi::receive_16};

PotMemF spi::ptr_transmite[2] = {&spi::transmit_8, &spi::transmit_16};
ptr_ex spi::ptr_exchange[2] =  {&spi::exchange_8, &spi::exchange_16};

spi::spi (SPI_N spi_, PORT p, Division div, CS_MODE mode_, Cpol cpl, Cpha cph, Role r, Size s)
:pin (p)
{
	nspi_ = spi_;
	//tact SPI
	SIM->SCGC4 |= 1 << nspi_;
	port_ = p;
	size_ = s;

  //tact SPI


}
/*
void spi::Set_CS ()
{

}

void spi::Clear_CS ()
{

}

void spi::transmit_8 (uint16_t data)
{

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
}*/

