#include "MKL17Z4.h"                    // Device header
#include "pin.h"
#include "delay.h"
#include "mcglight.h"

Tact frq;

int main ()
{
	Pin pins (Gpio::A, 0);
	while (1)
	{
		pins.togle();
		delay_ms(1000);
	}
}
