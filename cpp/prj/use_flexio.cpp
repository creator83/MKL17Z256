#include "MKL17Z4.h"                    // Device header
#include "tact.h"
#include "flexio.h"
#include "delay.h"

Tact frq;


int main (){

	Flexio spiTouch (Flexio::interface::spi, Flexio::nBuffer::buffer0);
	while (1){
		spiTouch.transmite(0x0F);
		delay_ms(200);
		spiTouch.transmite(0xF0);
		delay_ms(200);
	}
}
