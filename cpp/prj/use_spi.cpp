#include "MK10D10.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"

tact frq;
const char CS=9;
const char SCK=11;
const char MOSI=16;
const char MISO=17;

//Tact port A
Gpio spi_pin (Gpio::B);

void spi1_transmit (uint8_t data);
void spi1_init ();

int main()
{
	spi1_init ();

  while (1)
  {

	  	//spi_pin.clearPin(CS);
	  	spi1_transmit (0x0F);
		//spi_pin.setPin(CS);
		delay_ms (1000);
		//spi_pin.clearPin(CS);
		spi1_transmit (0xF0);
		//spi_pin.setPin(CS);
		delay_ms (1000);
  }
}

void spi1_init ()
{

	//Setting pin CS as digital out
	//spi_pin.setOutPin(CS);

	//
	//spi_pin.setPin(CS);

	//Settings pins SCK, MOSI, MISO as ALT2
	spi_pin.setOutPort((1 << CS|1 << SCK|1 << MOSI|1 << MISO), Gpio::Alt2);

	//Turn on tacting SPI0
	SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;

	//Settings SPI1
	SPI1->MCR = SPI_MCR_MSTR_MASK | SPI_MCR_PCSIS(2) | SPI_MCR_HALT_MASK;



	//SPI1_MCR = SPI_MCR_MSTR_MASK | SPI_MCR_ROOE_MASK | SPI_MCR_PCSIS(2) | SPI_MCR_DIS_TXF_MASK | SPI_MCR_DIS_RXF_MASK | SPI_MCR_CLR_TXF_MASK | SPI_MCR_CLR_RXF_MASK | SPI_MCR_HALT_MASK; //Set Configuration register

	SPI1->CTAR[0] = SPI_CTAR_DBR_MASK | SPI_CTAR_FMSZ(7) | SPI_CTAR_PCSSCK(1) | SPI_CTAR_PASC(1) | SPI_CTAR_PDT(1) | SPI_CTAR_PBR(1) | SPI_CTAR_CSSCK(0x0C) | SPI_CTAR_ASC(0x0C) | SPI_CTAR_DT(0x0C) | SPI_CTAR_BR(0x0E);

	//SPI0->CTAR[1] &= ~ (SPI_CTAR_CPHA_MASK|SPI_CTAR_CPOL_MASK|SPI_CTAR_LSBFE_MASK);
	//SPI1->CTAR[0] = SPI_CTAR_FMSZ(7) | SPI_CTAR_BR(0x0E);

	SPI1->SR = SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK | SPI_SR_TXCTR(0) | SPI_SR_TXNXTPTR(0) | SPI_SR_RXCTR(0) | SPI_SR_POPNXTPTR(0); //Clear flags

	SPI0->MCR &= ~SPI_MCR_HALT_MASK;
}

void spi1_transmit (uint8_t data)
{
	while(!(SPI0->SR & SPI_SR_TCF_MASK));
	SPI0->PUSHR =SPI_PUSHR_PCS(2)| SPI_PUSHR_TXDATA(data);
}

