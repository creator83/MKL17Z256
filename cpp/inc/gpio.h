#include "MKL17Z4.h"      


#ifndef GPIO_H
#define GPIO_H

typedef unsigned int* reg;


class Gpio
{
//variables
public:
  enum Port {A , B , C , D, E};
  enum mode {Alt0 , Alt1 , Alt2 , Alt3, Alt4 , Alt5 , Alt6};
	enum dir {Input, Output};
  enum speed {Low = 0 , Medium = 1 , High=3};
  enum out {PushPull , OpenDrain};
  enum PP {NoPP , PullUp , PullDown};
  enum rgstr {
  PDOR = 0x00,
  PSOR = 0x04,
  PCOR = 0x08,
  PTOR = 0x0C,
  PDIR = 0x10,
  PDDR = 0x14,
	GPCLR = 0x80,
	GPCHR = 0x84
};
protected:
private:
  static unsigned int portAdr [5];
	static unsigned int portAdrSet [5];
  static unsigned int portAdrBit [6];  
//static unsigned int pAdr [3];	
  unsigned char prt;
//functions
public:
  Gpio(Port p );
  Gpio(uint8_t p );
  void setOutPin (unsigned char pin, mode m = Alt1, dir d = Output);	
  void setPin (unsigned int pin);
  void clearPin (unsigned char pin);	
  void setValPort (unsigned int value);	
  void setOutPort (unsigned int value);		
  void ChangePinState (unsigned char pin);
  void SetPinState (unsigned char pin , unsigned char state);
  void PuPd (unsigned char pin , PP p);
  bool PinState (unsigned char pin);
}; //Gpio


#endif
