#include "port.h"

Port::Port (Gpio::Port prt, uint32_t value)
:Gpio(prt), value_(value)
{
	union
	{
		uint32_t full;
		uint16_t half[2];
	}val;
	val.full = value_;
	PORT_GPCLR_REG(PortBase[Gpio::prt]) = (val.half[0]<<16| (uint8_t)Gpio::mode::Output << PORT_PCR_MUX_SHIFT);
	PORT_GPCHR_REG(PortBase[Gpio::prt]) = (val.half[1]<<16| (uint8_t)Gpio::mode::Output << PORT_PCR_MUX_SHIFT);
	GPIO_PDDR_REG(GpioBase [Gpio::prt]) |= value;
}

Port::Port (Gpio::Port prt, mux mx, uint32_t value)
:Gpio(prt)
{
	union
	{
		uint32_t full;
		uint16_t half[2];
	}val;
	val.full = value;
	PORT_GPCLR_REG(PortBase[Gpio::prt]) = (val.half[0]<<16| (uint8_t)mx << PORT_PCR_MUX_SHIFT);
	PORT_GPCHR_REG(PortBase[Gpio::prt]) = (val.half[1]<<16| (uint8_t)mx << PORT_PCR_MUX_SHIFT);
}

void Port::set(uint32_t value)
{
	GPIO_PSOR_REG(GpioBase[prt])  |= value;
}

void Port::set()
{
	GPIO_PSOR_REG(GpioBase[prt])  |= value_;
}

void Port::set (uint32_t value, bool st)
{

}

void Port::clear (uint32_t value)
{
	GPIO_PCOR_REG(GpioBase[prt])  |= value;
}

void Port::clear ()
{
	GPIO_PCOR_REG(GpioBase[prt])  |= value_;
}

void Port::togle (uint32_t value)
{
	GPIO_PTOR_REG(GpioBase[prt])  |= value;
}
