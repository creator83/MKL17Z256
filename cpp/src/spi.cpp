#include "spi.h"
#include "MKL17Z4.h"

//CS,SCK,MISO,MOSI

uint8_t spi::pins_d[2][4]={{4,5,6,7},{6,3,4,5}};

PotMemFn spi::ptr_receive[2] = {&spi::receive_8, &spi::receive_16};

PotMemF spi::ptr_transmite[2] = {&spi::transmit_8, &spi::transmit_16};
ptr_ex spi::ptr_exchange[2] =  {&spi::exchange_8, &spi::exchange_16};
/*
spi::spi (SPI_N spi_, PORT p, Division div, PORT_CS p_cs, uint8_t pin, Cpol cpl, Cpha cph, Role r, Size s)
:pin (p)
{
	nspi_ = spi_;
	//tact SPI
	SIM->SCGC4 |= 1 << nspi_;
	port_ = p;
	size_ = s;

  //tact SPI


}*/

spi::spi()
:pin(Gpio::C)
{
	//Settings pins

	//CS
	pin.setOutPin(CS,Gpio::Alt1,Gpio::Output);

	//SCK
	pin.setOutPin(SCK,Gpio::Alt2, Gpio::Output);

	//MOSI
	pin.setOutPin(MOSI,Gpio::Alt2, Gpio::Output);

	//MISO
	pin.setOutPin(MISO,Gpio::Alt2, Gpio::Input);


	//Settings SPI0
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK ;

	SPI0->C2 &= ~SPI_C2_SPIMODE_MASK;
	SPI0->BR = SPI_BR_SPR(5);
	SPI0->C2 |= SPI_C2_MODFEN_MASK;
	SPI0->C1 |= SPI_C1_MSTR_MASK|SPI_C1_SPE_MASK|SPI_C1_SSOE_MASK;

}

void spi::transmit_8 (uint16_t data)
{
	if (!flag_sptef ());
	SPI0->DL |= (uint8_t)data;
}

void spi::Set_CS ()
{
	pin.setPin(CS);

}

void spi::Clear_CS ()
{
	pin.clearPin(CS);
}
/*





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

