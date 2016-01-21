#include "gpio.h"


unsigned int Gpio::portAdr [5] = {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE};
unsigned int Gpio::portAdrSet [5] = {PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE};
unsigned int Gpio::portAdrBit [6] = {0x42000000, 0x42000400, 0x42000800,0,0,0x42001400};

Gpio::Gpio (Port p)
{
  prt = p;
//takt port
  SIM->SCGC5 |= (0x200 << p);
}

Gpio::Gpio(uint8_t p )
{
  prt = p;
//takt port
  SIM->SCGC5 |= (0x200 << p);
}

void Gpio::setOutPin (uint8_t pin, mode m, dir d)
{
	*(reg)(portAdrSet[prt]+pin*4) |= (0x80 << m);
	*(reg)(portAdr[prt]+PDDR) &= ~(1 << pin);
	*(reg)(portAdr[prt]+PDDR) |= (d << pin);
}

void Gpio::setPin (uint8_t pin)
{
  *(reg)(portAdr[prt]+PSOR) |= 1 << pin;
}

void Gpio::clearPin (uint8_t pin)
{
  *(reg)(portAdr[prt]+PCOR) |= (1 << pin);
}

void Gpio::ChangePinState (uint8_t pin)
{
  *(reg)(portAdr[prt]+PTOR) = 1 << pin;
}

void Gpio::SetPinState (uint8_t pin , uint8_t state)
{
  if (state)setPin (pin);
  else clearPin (pin);  
}

void Gpio::test ()
{
	*(reg)(portAdrSet[prt]+GPCHR)|= (1<<16)|(Alt1 << 8);
	*(reg)(portAdr[prt]+PDDR) |= 1 << 16;
}

void Gpio::setOutPort (uint32_t value)
{
  /*  for (uint8_t i = 0;i<32;++i)
  {
    if (value & (1<<i))
    {
      *(reg)(portAdrSet[prt]+i*4) |= (0x80 << Alt1);
    }
    
  }*/
//  *(reg)(portAdr[prt]+PDDR) &= ~value;
  

	*(reg)(portAdrSet[prt]+GPCLR) |= ((0x0000FFFF&value)<<16)|(Alt1 << 8);
	*(reg)(portAdrSet[prt]+GPCHR) |= (0xFFFF0000&value)|(Alt1 << 8);
	*(reg)(portAdr[prt]+PDDR) |= value;
}

void Gpio::setValPort (uint32_t value)
{
  *(reg)(portAdr[prt]+PSOR) |= value;
}

void Gpio::clearValPort (uint32_t value)
{
	*(reg)(portAdr[prt]+PCOR) |= value;
}

bool Gpio::PinState (uint8_t pin)
{
  return ((*(reg)(portAdr[prt]+PDIR))&(1 << pin));
}
