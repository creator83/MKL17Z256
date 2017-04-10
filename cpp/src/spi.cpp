#include "spi.h"

SPI_MemMapPtr Spi::spiAdr [2]={SPI0_BASE_PTR, SPI1_BASE_PTR};

PotMemFn Spi::ptr_receive[2] = {};

PotMemF Spi::ptr_transmite[2] = {};
ptr_ex Spi::ptr_exchange[2] =  {};



Spi::Spi(SPI_N n, Division d, Cpol cpol, Cpha cpha, Size s, Mode m, Role r)
{
  n_spi = (uint8_t) n;
  size_ = (uint8_t)s;
  cpol_ = (uint8_t)cpol;
  cpha_ = (uint8_t)cpha;
  role_ = (uint8_t)r;
  div_ = (uint8_t)d;
  mode_ = (uint8_t)m;

  //Turn on tacting SPI1
  SIM->SCGC4 |= 1 << (SIM_SCGC4_SPI0_SHIFT + n_spi);

  //===Settings SPI1===//
  SPI_S_REG(spiAdr [n_spi]) = 0x00;
  SPI_C2_REG(spiAdr [n_spi]) &= ~SPI_C2_MODFEN_MASK;
  SPI_BR_REG(spiAdr [n_spi]) = SPI_BR_SPR(div_);
  SPI_C2_REG(spiAdr [n_spi]) |= mode_ << SPI_C2_MODFEN_SHIFT|(size_<<SPI_C2_SPIMODE_SHIFT);
  SPI_C1_REG(spiAdr [n_spi]) &= ~(SPI_C1_MSTR_MASK |SPI_C1_CPHA_MASK|SPI_C1_CPOL_MASK|SPI_C1_SSOE_MASK);
  SPI_C1_REG(spiAdr [n_spi]) |= (role_ << SPI_C1_MSTR_SHIFT|cpol_ << SPI_C1_CPOL_SHIFT |cpha_ << SPI_C1_CPHA_SHIFT|mode_ <<  SPI_C1_SSOE_SHIFT);
}

Spi::Spi (SPI_N n, Role r )
{
	n_spi = (uint8_t) n;
	role_ = (uint8_t)r;
	//Turn on tacting SPI1
	SIM->SCGC4 |= 1 << (SIM_SCGC4_SPI0_SHIFT + n_spi);

	//===Settings SPI1===//
	SPI_C1_REG(spiAdr [n_spi]) &= ~(SPI_C1_MSTR_MASK |SPI_C1_CPHA_MASK|SPI_C1_CPOL_MASK);
	SPI_C1_REG(spiAdr [n_spi]) |= role_ << SPI_C1_MSTR_SHIFT;
}

void Spi::start ()
{
	SPI_C1_REG(spiAdr [n_spi]) |= SPI_C1_SPE_MASK;
}

void Spi::stop ()
{
	SPI_C1_REG(spiAdr [n_spi]) &= ~ SPI_C1_SPE_MASK;
}

void Spi::setCpol (Cpol c)
{
	 SPI_C1_REG(spiAdr [n_spi]) &= ~SPI_C1_CPOL_MASK;
	 SPI_C1_REG(spiAdr [n_spi]) |= (uint8_t)c << SPI_C1_CPOL_SHIFT;
}

void Spi::setCpha (Cpha c)
{
	SPI_C1_REG(spiAdr [n_spi]) &= ~SPI_C1_CPHA_MASK;
	SPI_C1_REG(spiAdr [n_spi]) |= (uint8_t)c << SPI_C1_CPHA_SHIFT;
}

void Spi::setDivision (Division d)
{
	SPI_BR_REG(spiAdr [n_spi]) = SPI_BR_SPR(uint8_t (d));
}

void Spi::setFrameSize (Size s)
{
	SPI_C2_REG(spiAdr [n_spi]) &= ~SPI_C2_SPIMODE_MASK;
	SPI_C2_REG(spiAdr [n_spi]) |= (uint8_t)s << SPI_C2_SPIMODE_SHIFT;
}

void Spi::setMode (Mode m)
{
	SPI_C2_REG(spiAdr [n_spi]) &= ~SPI_C2_MODFEN_MASK;
	SPI_C2_REG(spiAdr [n_spi]) |= (uint8_t)m << SPI_C2_MODFEN_SHIFT;
	SPI_C1_REG(spiAdr [n_spi]) &= ~SPI_C1_SSOE_MASK;
	SPI_C1_REG(spiAdr [n_spi]) |= (uint8_t)m << SPI_C1_SSOE_SHIFT;
}

void Spi::setDma (Dma &d)
{
	driverDma = &d;
	DMA0->DMA[d.getChannel()].DCR |= DMA_DCR_CS_MASK;
	DMA0->DMA[d.getChannel()].DCR |= DMA_DCR_EADREQ_MASK| DMA_DCR_ERQ_MASK;
}

void Spi::enableDma (dma d)
{
	SPI_C2_REG(spiAdr [n_spi]) |= (1 << (uint8_t)d);
}

void Spi::disableDma (dma d)
{
	SPI_C2_REG(spiAdr [n_spi]) &= ~(1 << (uint8_t)d);
}

void Spi::putDataDh (uint8_t data)
{
	SPI_DH_REG(spiAdr[n_spi]) = data;
}

void Spi::putDataDl (uint8_t data)
{
	SPI_DL_REG(spiAdr[n_spi]) = data;
}
uint8_t Spi::getDataDh ()
{
	return SPI_DH_REG(spiAdr[n_spi]);
}
uint8_t Spi::getDataDl ()
{
	return SPI_DL_REG(spiAdr[n_spi]);
}
bool Spi::flagSptef ()
{
	return SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK;
}

bool Spi::flagSprf ()
{
	return SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPRF_MASK;
}

SPI_MemMapPtr & Spi::getSpiPtr ()
{
	return spiAdr[n_spi];
}
