#include "MKL26Z4.h"            // Device header


#ifndef GPIO_H
#define GPIO_H



class Gpio
{
//variables
public:
  enum Port {A , B , C , D , E};
  enum mux {Analog, GPIO , Alt2 , Alt3 , Alt4 , Alt5 , Alt6 , Alt7};
  enum mode {Input, Output};
  enum PP {PullDown, PullUp};
  enum state {Off, On};

protected:
  static PORT_MemMapPtr PortBase [5];
  static FGPIO_MemMapPtr GpioBase [5];
  uint8_t prt;
private:

//functions
public:
  Gpio ();
  Gpio(Port p );
  void setPort (Port p);

  //function for port
  void settingPort (uint32_t val, mux mx = GPIO, mode m = Output);
  void settingPortDirection (uint32_t val, mode m);
  void setValPort (uint32_t value);
  void clearValPort (uint32_t value);
};

#endif



