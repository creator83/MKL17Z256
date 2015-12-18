#include "MKL17Z4.h"                 // Device header
#include "gpio.h"


#ifndef UART_H
#define UART_H

typedef unsigned int* reg;

const uint16_t uart0clk = 48000;

class uart
{
//variables
public:
  enum baud {baud9600 = 9600 , baud57600 = 57600 , baud115200 = 115200};
private:
  Gpio pin;
  enum pin_def {TX = 22 , RX};
//functions
public:
  uart (baud b);
  void transmit (uint8_t data);
  void transmit (char * str);  
  uint8_t receive ();
};

#endif
