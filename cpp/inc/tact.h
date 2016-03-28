#include "MKL17Z4.h"               // Device header

#ifndef TACT_H
#define TACT_H


class tact
{
  //variables
public:
  enum mode {LIRC_8,HIRC,EXT,LIRC_2};

 private:
  static uint8_t cpu_clock;
  static uint8_t bus_clock;
  uint8_t src;
  //functions
public:
  tact ();
  tact (mode m, uint8_t frq);
  static uint8_t & get_frq_cpu (){return cpu_clock;};
  static uint8_t & get_frq_bus (){return bus_clock;};
private:
  //===int_OSC===//

  void init_LIRC_8 (uint8_t i);

  void init_LIRC_2 (uint8_t i);
  //
  void init_HIRC ();

  //===ext_OSC===//

  void init_EXT (uint8_t i);

  void Set_frq (uint8_t frq);

};

 
#endif

