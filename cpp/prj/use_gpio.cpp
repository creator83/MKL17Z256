#include "MKL17Z4.h"                    // Device header
#include "pin.h"
#include "delay.h"
#include "mcglight.h"
#include "ili9341.h"
Tact frq;

int main ()
{
	Pin light (Gpio::C, 3);
	light.set();

	while (1)
	{

	}
}
