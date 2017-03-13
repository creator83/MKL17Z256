#include "gpio.h"

GPIO_MemMapPtr Gpio::GpioBase [5] = {GPIOA_BASE_PTR , GPIOB_BASE_PTR , GPIOC_BASE_PTR, GPIOD_BASE_PTR, GPIOE_BASE_PTR};
PORT_MemMapPtr Gpio::PortBase [5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};


Gpio::Gpio ()
{

}

Gpio::Gpio (Port p)
{
  prt = static_cast <uint8_t> (p);
  //takt port
  SIM->SCGC5 |= (0x200 << prt);
}





