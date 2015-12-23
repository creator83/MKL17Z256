#include "MKL17Z4.h"                    // Device header
#include "gpio.h"


int main ()
{
	Gpio E (Gpio::E);
	E.setOutPin (23);
	E.setPin (23);
	
	while (1)
	{
		
	}
}
