#include "MKL17Z4.h"              // Device header
#include "gpio.h"


/*
 SPI0
 Alt2
 C: CS-4, SCK-5, MOSI-6, MISO-7
 D: CS-0, SCK-1, MOSI-2, MISO-3
 E: CS-16, SCK-17, MOSI-18, MISO-19
 SPI1
 D: CS-4, SCK-5, MOSI-6, MISO-7

*/

#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;
typedef uint16_t(spi::*ptr_ex)(uint16_t) ;

typedef void(spi::*PotMemF)(uint16_t) ;

class spi
{
//variables
public:
  enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256, div512};
  enum SPI_N {SPI_0 = 22, SPI_1};
  enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
  static uint8_t pins_d[2][4];
  enum Size {bit8, bit16};
  enum PORT {C,D,E};
  enum CS_MODE {CS_HARDWARE,CS_SOFTWARE};
	
  enum pin_def {CS=4, SCK ,  MOSI, MISO};
  uint8_t port_;
  uint8_t size_;
  uint8_t nspi_;
private:
  Gpio pin;
  static PotMemFn ptr_receive[2];
  static PotMemF ptr_transmite[2];
  static ptr_ex ptr_exchange[2];

//functions
public:
  //constructor for software mode
  //spi(SPI_N spi_, PORT p, Division div, PORT_CS p_cs, uint8_t pin, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
  //constructor for hardware mode
  //spi(SPI_N spi_, PORT p, Division div, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
  spi();
  void Set_CS ();
  void Clear_CS ();
  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
  void transmit (uint16_t data);
  uint16_t receive_8 ();
  uint16_t receive_16 ();
  uint16_t receive ();

  uint16_t exchange_8 (uint16_t data);
  uint16_t exchange_16 (uint16_t data);
  uint16_t exchange (uint16_t data);
  bool flag_bsy ();
  bool flag_sptef ();
  bool flag_rxne ();
private:
};

inline bool spi::flag_sptef (){return SPI0->S&SPI_S_SPTEF_MASK;}

#endif

