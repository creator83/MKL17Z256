#include "MKL17Z4.h"                    // Device header
#include "gpio.h"


int main ()
{
	Gpio A (Gpio::A);
	A.setOutPin (0);
	A.setPin (0);
	
	while (1)
	{
		
	}
}
