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
  spi(SPI_N n, PORT p, Division d_, Role r=master, Cpol cpol_=neg, Cpha cpha_=first, Size s=bit8 );
  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
  void transmit (uint16_t data);
  uint16_t receive_8 ();
  uint16_t receive_16 ();
  uint16_t receive ();

  uint16_t exchange_8 (uint16_t data);
  uint16_t exchange_16 (uint16_t data);
  uint16_t exchange (uint16_t data);

  void put_data_dh (uint8_t data);
  void put_data_dl (uint8_t data);
  uint8_t get_data_dh ();
  uint8_t get_data_dl ();
  bool flag_sptef ();
  bool flag_sprf ();

private:
};

inline void spi::put_data_dh (uint8_t data){SPI0->DH = data;}
inline void spi::put_data_dl (uint8_t data){SPI0->DL = data;}
inline uint8_t spi::get_data_dh (){return SPI0->DH;}
inline uint8_t spi::get_data_dl (){return SPI0->DL;}
inline bool spi::flag_sptef (){return SPI0->S & SPI_S_SPTEF_MASK;}
inline bool spi::flag_sprf (){return SPI0->S & SPI_S_SPRF_MASK;}


#endif

