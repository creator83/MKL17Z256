#include "device.h"               // Device header
#include "shape.h"
#include "colors16bit.h"

#ifndef CPIC_H
#define CPIC_H

class ColorPicture : public Shape
{
private:
	uint16_t x, y, length, width;
	const uint16_t * arr;

public:

	ColorPicture (uint16_t x_, uint16_t y_, const uint16_t * pic, uint16_t length_, uint16_t width_);

	void draw () const override;

};

#endif
