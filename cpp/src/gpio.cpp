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

void Gpio::setOutPin (unsigned char pin, mode m, dir d)
{
	*(reg)(portAdrSet[prt]+pin*4) |= (0x100 << m);
	*(reg)(portAdr[prt]+PDDR) &= ~(1 << pin);
	*(reg)(portAdr[prt]+PDDR) |= (d << pin);
}

void Gpio::setPin (unsigned int pin )
{
  *(reg)(portAdr[prt]+PSOR) |= 1 << pin;
}

void Gpio::clearPin (unsigned char pin)
{
  *(reg)(portAdr[prt]+PCOR) |= (1 << pin);
}

void Gpio::ChangePinState (unsigned char pin)
{
  *(reg)(portAdr[prt]+PTOR) = 1 << pin;
}

void Gpio::SetPinState (unsigned char pin , unsigned char state)
{
  if (state)setPin (pin);
  else clearPin (pin);  
}

void Gpio::setOutPort (unsigned int value)
{
	*(reg)(portAdrSet[prt]+GPCLR) = ((0x0000FFFF&value)<<16);
	*(reg)(portAdrSet[prt]+GPCLR) |= (100 << Alt1);
	*(reg)(portAdrSet[prt]+GPCHR) = ((0xFFFF0000&value)<<16);
	*(reg)(portAdrSet[prt]+GPCHR) |= (100 << Alt1);
}

void Gpio::setValPort (unsigned int value)
{
  *(reg)(portAdr[prt]+PSOR) = value;
}

bool Gpio::PinState (unsigned char pin)
{
  return ((*(reg)(portAdr[prt]+PDIR))&(1 << pin));
}
