#include "flashspi.h"



Flash::Flash (Spi &d, Gpio::Port p, uint8_t pin)
:cs(p, pin)
{
	driver = &d;
	driver->setCpol(Spi::Cpol::neg);
	driver->setCpha(Spi::Cpha::first);
	driver->setDivision(Spi::Division::div32);
	driver->setFrameSize(Spi::Size::bit8);
	cs.set();
	driver->start();
	delay_ms(5);
	powerUp ();
}

void Flash::writeByte (uint8_t)
{

}

void Flash::writePage (const uint8_t * buffer, uint32_t addr, uint16_t n)
{
	writeEnable ();
	cs.clear();
	command(flashCommands::PageProgram);
	command(addr>>16);
	command(addr>>8);
	command(addr);
	for (uint16_t i=0;i<n;++i)
	{
		command(*buffer++);
	}
	cs.set();
	while (flagBusy());
}

void Flash::writePage16 (const uint16_t * buffer, uint32_t addr, uint16_t n)
{
	writeEnable ();
	driver->setFrameSize (Spi::Size::bit16);
	cs.clear();
	command16(flashCommands::PageProgram, addr>>16);
	command16(addr>>8, addr);
	for (uint16_t i=0;i<n;++i)
	{
		command16(*buffer>>8, *buffer);
		++buffer;
	}
	cs.set();
	driver->setFrameSize (Spi::Size::bit8);
	while (flagBusy());
}

void Flash::write (uint8_t * buffer, uint32_t addr, uint16_t n)
{

}

void Flash::readID ()
{
	/*cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(ManufactDeviceID);
	while (!driver->flagSprf());
	uint8_t dummy = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl(0);
	while (!driver->flagSprf());
	manufacturId = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl(0);
	while (!driver->flagSprf());
	deviceId = driver->getDataDl()<<8;
	while (!driver->flagSptef());
	driver->putDataDl(0);
	while (!driver->flagSprf());
	deviceId |= driver->getDataDl();
	cs.set();*/
}

uint16_t Flash::readStatus1 ()
{
	cs.clear();
	command(flashCommands::ReadStatusReg1);
	uint8_t status = command(0);
	cs.set();
	return status;
}

uint16_t Flash::readStatus2 ()
{
	cs.clear();
	command(flashCommands::ReadStatusReg2);
	uint8_t status = command(0);
	cs.set();
	return status;
}

uint16_t Flash::readStatus3 ()
{
	cs.clear();
	command(flashCommands::ReadStatusReg3);
	uint8_t status = command(0);
	cs.set();
	return status;
}

void Flash::writeStatus (uint8_t val)
{
	cs.clear();
	command(flashCommands::WriteStatusReg);
	command(val);
	cs.set();
}

void Flash::writeEnable ()
{
	cs.clear();
	command(flashCommands::WriteEnable);
	cs.set();
}

void Flash::writeDisable ()
{
	/*cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(WriteDisable);
	while (!driver->flagSptef());
	cs.set();*/
}

void Flash::read (uint8_t * buffer, uint32_t addr, uint16_t n)
{
	cs.clear();
	command(flashCommands::ReadData);
	command(addr>>16);
	command(addr>>8);
	command(addr);
	for (uint16_t i=0;i<n;++i)
	{
		*buffer++ = command(0);
	}
	cs.set();
}

void Flash::read16 (uint16_t * buffer, uint32_t addr, uint16_t n)
{
	driver->setFrameSize (Spi::Size::bit16);
	cs.clear();
	command16(flashCommands::ReadData, addr>>16);
	command16(addr>>8, addr);
	for (uint16_t i=0;i<n;++i)
	{
		*buffer++ = command16(0, 0);
	}
	cs.set();
	driver->setFrameSize (Spi::Size::bit8);
}

void Flash::eraseSector (uint32_t addr)
{
	writeEnable();
	while (flagBusy());
	cs.clear();
	command(flashCommands::SectorErase);
	command(addr>>16);
	command(addr>>8);
	command(addr);
	cs.set();
	while (flagBusy());
}

void Flash::eraseChip ()
{
	writeEnable ();
	cs.clear();
	command(flashCommands::ChipErase);
	cs.set();
	while (flagBusy());
}

bool Flash::flagBusy ()
{
	return readStatus1()&0x01;
}

uint8_t Flash::command (uint8_t c)
{
	while (!driver->flagSptef());
	driver->putDataDl(c);
	while (!driver->flagSprf());
	return driver->getDataDl();
}

uint16_t Flash::command16 (uint8_t h, uint8_t l)
{
	while (!driver->flagSptef());
	driver->putDataDh(h);
	driver->putDataDl(l);
	while (!driver->flagSprf());
	uint16_t res = driver->getDataDh() << 8;
	res |= driver->getDataDl();
	return res;
}

void Flash::powerDown ()
{
	cs.clear();
	command(flashCommands::PowerDown);
	cs.set();
	delay_us(5);
}

void Flash::powerUp ()
{
	cs.clear();
	command(flashCommands::ReleasePowerDown);
	cs.set();
	delay_us(5);
}

void Flash::getCapacity ()
{

}
