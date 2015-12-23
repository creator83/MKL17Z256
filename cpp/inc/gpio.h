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
  enum PP {PullUp , PullDown};
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
  void setOutPin (uint8_t pin, mode m = Alt1, dir d = Output);	
  void setPin (uint8_t pin);
  void clearPin (uint8_t pin);	
  void setValPort (uint32_t value);	
	void clearValPort (uint32_t value);	
  void setOutPort (uint32_t value);		
  void ChangePinState (uint8_t pin);
  void SetPinState (uint8_t pin , uint8_t state);
  void PuPd (uint8_t pin , PP p);
  bool PinState (uint8_t pin);
}; //Gpio


#endif
