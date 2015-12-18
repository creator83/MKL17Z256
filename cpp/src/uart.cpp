#include "uart.h"


uart::uart (baud b)
:pin (Gpio::E)
{
  SIM->SCGC4|= SIM_SCGC4_UART2_MASK;
	uint16_t sbr;
  uint8_t temp;
  
  //Settings TX
  pin.setOutPin (TX , Gpio::Alt4);
  
  //Settings RX
  
  pin.setOutPin (RX , Gpio::Alt4);
  
  
  //===Settings UART===//
	//Disable UART
	UART2->C2 &= ~(UART_C2_RE_MASK|UART_C2_TE_MASK);
	UART2->C1 = 0;
	
	//calculate baud
	temp = UART0->C4;
	temp = (temp & 0x1F) + 1;
	sbr = (uint16_t)((uart0clk)/(b * (temp)));
	
	/* Save off the current value of the uartx_BDH except for the SBR field */
  temp = UART0->BDH & ~(UART_BDH_SBR(0x1F));
	
	UART2->BDH = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	UART2->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
	
  UART2->C2 |= (UART_C2_RE_MASK|UART_C2_TE_MASK);
}

void uart::transmit (uint8_t data)
{
	/* Wait until space is available in the FIFO */
  while(!(UART2->S1 & UART_S1_TDRE_MASK));
   
  /* Send the character */
  UART2->D = data;
}

void uart::transmit (char * str)
{
  while (*str)
  {
    while(!(UART2->S1 & UART_S1_TDRE_MASK));
    UART2->D = *str;
    str++;
  }
}
