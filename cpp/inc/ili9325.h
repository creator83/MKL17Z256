#include "MKL17Z4.h"              // Device header
#include "gpio.h"
#include "delay.h"

#ifndef ILI9325_H
#define ILI9325_H

//#define BIT8


const uint16_t BLACK   =	 0x0000;
const uint16_t BLUE	   =	 0x001F;
const uint16_t RED 	   =	 0xF800;
const uint16_t GREEN   =	 0x07E0;
const uint16_t CYAN	   =	 0x07FF;
const uint16_t MAGENTA =	 0xF81F;
const uint16_t YELLOW  =	 0xFFE0;
const uint16_t WHITE   =	 0xFFFF;

const uint16_t GRAY	   =	 0xE79C;
const uint16_t SKY     =	 0x5d1C;
const uint16_t ORANGE  =   0xFCA0;
const uint16_t PINK    =	 0xF97F;
const uint16_t BROWN   =	 0x8200;
const uint16_t VIOLET  =	 0x9199;
const uint16_t SILVER  =   0xA510;
const uint16_t GOLD    =	 0xA508;
const uint16_t BEGH    =	 0xF77B;
const uint16_t NAVY    =	 0x000F;
const uint16_t DARK_GREEN =  0x03E0;
const uint16_t DARK_CYAN  =	 0x03EF;
const uint16_t MAROON     =  0x7800;
const uint16_t PURPLE     =	 0x7BE0;
const uint16_t LIGHT_GREY =	 0xC618;
const uint16_t DARK_GREY  =  0x7BEF;


/*
************registers****************
*/


//GRAM area
const unsigned char h_Gram_start = 0x50;
const unsigned char h_Gram_end   = 0x51;
const unsigned char v_Gram_start = 0x52;
const unsigned char v_Gram_end   = 0x53;

//Entry mode
const unsigned char entry_mode = 0x03;

//Resize
const unsigned char resize = 0x04;


class ili9325
{
//variables
public:
	
protected:
private:
	enum commPins {RST=25, WR=30 , CS=24 , RS=29 ,RD=31};

#ifdef BIT8
	Gpio pinDataLow;
#else
	Gpio pinDataLow;
	Gpio pinDataHigh;
#endif
	Gpio pinCommand;
	unsigned int x_start, x_end, y_start, y_end;

//functions
public:
	ili9325();
	void point (uint16_t x , uint16_t y, uint16_t color);
	void fill_screen (uint16_t color);
	void set_area (uint16_t x1, uint16_t y1, uint16_t x2 , uint16_t y2);
	void set_cursor (uint16_t x , uint16_t y);
	void data (uint16_t dta);	
	void putchar (uint16_t x , uint16_t y , char * ch , uint16_t color , uint16_t background);

protected:
private:
	void init ();
	void index (uint16_t indx);

	//void wr_reg (unsigned int indx , unsigned int dta);
	void wr_reg (uint16_t indx , uint16_t dta);	

}; //ili9325

#endif //__ILI9325_H__
