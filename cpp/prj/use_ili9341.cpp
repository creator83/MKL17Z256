#include "MKL17Z4.h"                    // Device header
#include "ili9341.h"

Tact frq;
Spi spi0 (Spi::SPI_N::SPI_0);


int main ()
{
	Ili9341 display (spi0, Gpio::Port::D, 4, Gpio::Port::D, 5);
	while (1)
	{

	}
}
