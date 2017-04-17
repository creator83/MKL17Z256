#include "device.h"                    // Device header
#include "ili9341.h"
#include "colors16bit.h"
#include "font.h"
#include "mfont.h"
#include "flashspi.h"
//#include "rgb.h"
#include "flexio.h"
#include "pin.h"
#include "coffeebut.h"
#include "shape.h"
#include "cpic.h"

Tact frq;
Spi spiLcd (Spi::SPI_N::SPI_1);
Spi spimem (Spi::SPI_N::SPI_0);
Dma dma1 (Dma::dmaChannel::ch1);
Dma dma2 (Dma::dmaChannel::ch2);
Pit pit1 (Pit::ch1, 1);
//pins for lcd
	Pin cs (Gpio::Port::D, 4, Gpio::mux::Alt2);
	Pin sck (Gpio::Port::D, 5, Gpio::mux::Alt2);
	Pin mosi (Gpio::Port::D, 6, Gpio::mux::Alt2);
	Ili9341 display (spiLcd, Gpio::Port::D, 7, Gpio::Port::E, 0);

Pin csFxIo (Gpio::Port::E, 16, Gpio::mux::Alt6);
Pin sckFxIo (Gpio::Port::E, 17, Gpio::mux::Alt6);
Pin mosiFxIo (Gpio::Port::A, 18, Gpio::mux::Alt6);
Pin misoFxIo (Gpio::Port::A, 19, Gpio::mux::Alt6);

uint16_t c [5] = {colors16bit::BLACK, colors16bit::RED, colors16bit::BLUE, colors16bit::GREEN, colors16bit::YELLOW};

//uint8_t dest2 [25600];
//uint16_t monk [12800];
uint16_t buffer [8400];
uint16_t monk2 [50];
const uint16_t background = 0x0abb;


//ColorPicture buttonLight (0, 165, imgButtons::light16, 100, 70);
//Shape * mainScreen[] = {&buttonLight};

int main ()
{
	/*Tftdriver * lcd = &display;
	Shape::driver = lcd;*/
	//Flexio touchSpi (Flexio::interface::spi, Flexio::nBuffer::buffer0);
	//touchSpi.transmite(0xfe);
	Pin light (Gpio::Port::C, 3);
	light.set();

	//pins for memory
	Pin sckF (Gpio::Port::C, 5, Gpio::mux::Alt2);
	Pin mosiF (Gpio::Port::C, 6, Gpio::mux::Alt2);
	Pin misoF (Gpio::Port::C, 7, Gpio::mux::Alt2);


	Dma dma0 (Dma::dmaChannel::ch0);
	display.setDma(dma0);
	Flash memory (spimem, Gpio::Port::C, 4);
	memory.setDma( dma2, dma1, pit1);
	/*memory.writeEnable ();
	memory.readStatus ();*/
	//memory.read (dest, 0, 10);
	//memory.eraseChip ();
	/*uint32_t add=0;
		for (uint16_t i=0;i<600;++i, add+=128)
		{
			memory.writePage16 (&picture::monkeys[add], add, 128);
		}*/

	//memory.read (monk1, 0, 40);
	//memory.read16 (monk1, 0, 12800);
	//memory.txDum (20);
	display.fillScreenDma(&colors16bit::BLACK);
	display.drawPic(3,160, imgButtons::button1, 105, 80);
	display.drawPic(108,160, imgButtons::button1, 105, 80);
	display.drawPic(213,0, imgButtons::button1, 105, 80);
	display.drawPic(213,80, imgButtons::tools, 105, 80);
	display.drawPic(213,160, imgButtons::button1, 105, 80);
	//display.drawPic(0, 0, 320, 240);
	for (uint32_t i,j=0;i<154000;i+=12800, j+=20)
	{
		memory.txToDma ((uint32_t)buffer, i, 12800);
		display.drawPic(0,j, buffer, 320, 20);
	}

	//spiLcd.setFrameSize(Spi::Size::bit8);
	memory.txToDma ((uint32_t)monk2, 0, 100);
	/*uint32_t add=0;
	for (uint16_t i=0;i<600;++i, add+=256)
	{
		memory.writePage (&picture::monkeys[add], add, 256);
	}*/
	//memory.writePage (picture::monkeys, 0, 0xFF);
	//while (memory.flagBusy()) ++i;
	//memory.writeEnable ();

	//memory.read (dest2, 0, 25600);
	/*Font sFontRus (smallTimesNewRomanRus::simbols);
	sFontRus.setHeight(8);
	sFontRus.setWidth(8);
	sFontRus.setShift(32);
	Font rus (rusFont::times16);
	rus.setHeight(14);
	rus.setWidth(16);
	rus.setShift(192);

	display.symbol(50, 100, colors16bit::RED, colors16bit::YELLOW,  'B', sFontRus);
	display.string(50,50, colors16bit::RED, colors16bit::YELLOW, "Hello", sFontRus, 0);
	display.string(50,150, colors16bit::RED, colors16bit::YELLOW, "Русский", rus, -4);
	display.horLine(0,200, &colors16bit::BLUE, 320, 2);
	display.verLine(200,0, &colors16bit::BLUE, 240, 16);
	display.rectangle (20,20, &colors16bit::BLUE, 140, 80, 28);
	display.rectangle (100, 100, &colors16bit::CYAN, 100, 50);
	display.gradientVer(200,0, c, 119, 200);

	display.drawPic(0,0, monk1, 320, 40);*/
	while (1)
	{
		/*for (uint8_t i=0;i<5;++i){
			display.fillScreenDma(&c[i]);
			delay_ms(500);
		}
		delay_ms(2000);
		for (uint8_t i=0;i<5;++i){
			display.fillScreen(c[i]);
			delay_ms(500);
		}*/
	}
}
