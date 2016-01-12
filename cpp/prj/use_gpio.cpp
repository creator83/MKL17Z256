#include "MKL17Z4.h"                    // Device header
#include "gpio.h"
#include "delay.h"


int main ()
{
  Gpio E (Gpio::E);
  //E.setOutPin (16);
  E.setOutPort (0xF0000);
	
  //PORTE->GPCLR = ((PORTA_BIT6 | PORTA_BIT3 | PORTA_BIT0) | (PORT_MUX_GPIO | PORT_PS_UP_ENABLE | PORT_PFE));

  while (1)
  {
    E.setPin (16);
    delay_ms (1000);
    E.clearPin (16);
    delay_ms (1000);
  }
}
