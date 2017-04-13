#include "xpt2046.h"



Xpt2046::Xpt2046 (Spi &d)
:cs(xpt2046Def::csPort, xpt2046Def::csPin), irq (xpt2046Def::irqPort, xpt2046Def::irqPin, Intrpt::mode::fallingEdge),
 x(0), y(0), Xmin(300), Ymin(300), dX (3300), dY(3300)
{
	driver = &d;
	NVIC_EnableIRQ(PORTA_IRQn);
	driver->setCpol(Spi::Cpol::neg);
	driver->setCpha(Spi::Cpha::first);
	driver->setDivision(Spi::Division::div32);
	driver->setFrameSize(Spi::Size::bit8);
	cs.set ();
	driver->start();
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl(0x80);
	while (!driver->flagSprf());
	uint8_t dummy = driver->getDataDl();
	driver->putDataDl(0x00);
	while (!driver->flagSprf());
	dummy = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl(0x00);
	while (!driver->flagSprf());
	dummy = driver->getDataDl();
	cs.set();
}

void Xpt2046::getData ()
{
	uint16_t tempX, tempY;
	cs.clear();
	while (!driver->flagSptef());
	driver->putDataDl (channelX);
	while (!driver->flagSprf());
	uint8_t dummy = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl (0);
	while (!driver->flagSprf());
	tempX = driver->getDataDl();
	tempX <<= 8;
	while (!driver->flagSptef());
	driver->putDataDl (0);
	while (!driver->flagSprf());
	tempX |= driver->getDataDl();
	tempX >>=3;
	delay_us(100);
	driver->putDataDl (channelY);
	while (!driver->flagSprf());
	dummy = driver->getDataDl();
	while (!driver->flagSptef());
	driver->putDataDl (0);
	while (!driver->flagSprf());
	tempY = driver->getDataDl();
	tempY <<= 8;
	while (!driver->flagSptef());
	driver->putDataDl (0);
	while (!driver->flagSprf());
	tempY |= driver->getDataDl();
	tempY >>=3;
	cs.set();
	y = tempX-Xmin;
	x = 4096 - tempY-Ymin;
}

uint16_t & Xpt2046::getX ()
{
	return x;
}

uint16_t & Xpt2046::getY ()
{
	return y;
}

uint16_t & Xpt2046::getdX ()
{
	return dX;
}

uint16_t & Xpt2046::getdY ()
{
	return dY;
}

void Xpt2046::clearFlag ()
{
	irq.clearFlag();
}



