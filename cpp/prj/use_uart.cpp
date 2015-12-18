#include "MKL17Z4.h"                    // Device header
#include "uart.h"


int main ()
{
	uart uart2 (uart::baud9600);
	uart2.transmit ("Hello from Freescale!!!");
	while (1)
	{
		
		
	}
}
