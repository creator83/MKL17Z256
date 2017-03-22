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
}

void Flash::writeByte (uint8_t)
{

}

void Flash::writePage (uint8_t * buffer, uint32_t addr, uint16_t n)
{
	writeEnable();
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(PageProgram);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>16);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>8);
	while (!driver->flagSptef());
	driver->putDataDl(addr);
	for (uint16_t i=0;i<n;++i)
	{
		while (!driver->flagSptef());
		driver->putDataDl(*buffer++);
	}
	cs.set();
}

void Flash::write (uint8_t * buffer, uint32_t addr, uint16_t n)
{

}

void Flash::readID ()
{
	cs.clear();
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
	cs.set();
}

uint16_t Flash::readStatus ()
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(ReadStatusReg);
	while (!driver->flagSprf());
	uint8_t dummy = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl(0);
	while (!driver->flagSprf());
	uint16_t status = driver->getDataDl();
	cs.set();
}

void Flash::writeStatus (uint8_t val)
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(WriteStatusReg);
	while (!driver->flagSptef());
	driver->putDataDl(val);
	while (!driver->flagSptef());
	/*while (!driver->flagSprf());
	uint16_t status = driver->getDataDl();*/
	cs.set();
}

void Flash::writeEnable ()
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(WriteEnable);
	while (!driver->flagSptef());
	cs.set();
}

void Flash::writeDisable ()
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(WriteDisable);
	while (!driver->flagSptef());
	cs.set();
}

void Flash::read (uint8_t * buffer, uint32_t addr, uint16_t n)
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(ReadData);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>16);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>8);
	while (!driver->flagSptef());
	driver->putDataDl(addr);
	for (uint16_t i=0;i<n;++i)
	{
		while (!driver->flagSprf());
		*buffer++ = driver->getDataDl();
	}
	cs.set();
}

void Flash::eraseSector (uint32_t addr)
{
	writeEnable();
	while (flagBusy());
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(SectorErase);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>16);
	while (!driver->flagSptef());
	driver->putDataDl(addr>>8);
	while (!driver->flagSptef());
	driver->putDataDl(addr);
	cs.set();
	while (flagBusy());
}

void Flash::eraseChip ()
{
	writeEnable();
	while (flagBusy());
	cs.clear();
	driver->putDataDl(ChipErase);
	while (!driver->flagSptef());
	cs.set();
	while (flagBusy());
}

bool Flash::flagBusy ()
{
	return readStatus()&0x01;
}

void Flash::powerDown ()
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(PowerDown);
	while (!driver->flagSptef());
	cs.set();
	delay_us(3);
}

void Flash::powerUp ()
{
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(ReleasePowerDown);
	while (!driver->flagSptef());
	cs.set();
	delay_us(3);
}

void Flash::getCapacity ()
{

}

