#include "MKL17Z4.h"               // Device header

#ifndef TACT_H
#define TACT_H


class tact
{
  //variables
public:
  enum mode {LIRC_2, LIRC_8, HIRC, EXT};
  enum divider {div1, div2, div4, div8, div16, div32, div64, div128};

 private:
  static uint8_t cpu_clock;
  static uint8_t bus_clock;
  static uint8_t mcgir_clock;
  uint8_t src;
  //functions
public:
  tact ();
  tact (mode m, uint8_t frq);
  static uint8_t & get_frq_cpu (){return cpu_clock;};
  static uint8_t & get_frq_bus (){return bus_clock;};
  static uint8_t & get_frq_mcgir (){return mcgir_clock;};
  void get_LIRC_8 (divider div_1=div1, divider div_2=div1);

  void get_LIRC_2 (divider div_1=div1, divider div_2=div1);

  void set_LIRC_div (mode m, divider div_1, divider div_2);

private:

  void init_HIRC ();

  //===ext_OSC===//

  void get_EXT (uint8_t i);

  void Set_frq (uint8_t frq);

};

 
#endif

