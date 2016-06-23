#include "MKL17Z4.h"                 // Device header
#include "gpio.h"

#define SPI1_DR_8bit          (*(__IO uint8_t *)((uint32_t)&(SPI1->DR))) 


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

	
  enum pin_def {CS=4, SCK , MOSI, MISO};
  uint8_t port_;
  uint8_t size_;
private:
  gpio pin;
  static PotMemFn ptr_receive[2];
  static PotMemF ptr_transmite[2];
  static ptr_ex ptr_exchange[2];

//functions
public:
  spi();
  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
  void transmit (uint16_t data);
  uint16_t receive_8 ();
  uint16_t receive_16 ();
  uint16_t receive ();

  uint16_t exchange_8 (uint16_t data);
  uint16_t exchange_16 (uint16_t data);
  uint16_t exchange (uint16_t data);

private:
};

#endif

