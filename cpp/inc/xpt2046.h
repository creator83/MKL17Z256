#include "MKL26Z4.h"
#include "pin.h"
#include "spi.h"
#include "intrpt.h"
#include "delay.h"

#ifndef XPT2046_H
#define XPT2046_H

const uint8_t channelY = 0x90;
const uint8_t channelX = 0xD0;

namespace xpt2046Def
{
  //CS
  const Gpio::Port csPort = Gpio::E;
  const uint8_t csPin = 4;
  //IRQ
  const Gpio::Port irqPort = Gpio::A;
  const uint8_t irqPin = 1;
}


class Xpt2046
{
//variables
	uint16_t x, y;
	uint16_t Xmin, Ymin, dX, dY;
public:
  Pin cs;
  Spi * driver;
  Intrpt irq;

public:

  Xpt2046 (Spi &);
  void getData ();
  uint16_t & getX ();
  uint16_t & getY ();
  uint16_t & getdX ();
  uint16_t & getdY ();

  void clearFlag ();

};


#endif
