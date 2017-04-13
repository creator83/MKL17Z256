#include "cpic.h"

ColorPicture::ColorPicture (uint16_t x_, uint16_t y_, const uint16_t * pic, uint16_t length_, uint16_t width_)
:x(x_), y (y_), length (length_), width (width_), arr (pic)
{
}


void ColorPicture::draw () const
{
	driver->drawPic (x, y, arr, length, width);
}
