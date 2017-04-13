#include "device.h"                // Device header



#ifndef TFTDRIVER_H
#define TFTDRIVER_H

class Tftdriver
{
public:

public:
	virtual void drawPic (uint16_t x,uint16_t y, const uint16_t * arr,uint16_t length,uint16_t width) = 0;
	//virtual void horLine (uint16_t x, uint16_t y, const uint16_t color, uint16_t length, uint8_t thick) = 0;
	virtual ~Tftdriver(){}
};




#endif
