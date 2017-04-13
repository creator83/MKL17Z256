#include "MKL26Z4.h"               // Device header
#include "shape.h"
#include "colors16bit.h"

#ifndef SSTRING_H
#define SSTRING_H

class Sstring : public Shape
{
private:
	uint16_t x, y, color, fon;
	char * str;
	Ssd1289::sFont * font_;
	uint8_t interval, nChar;
public:
	Sstring (uint16_t x_, uint16_t y_, uint16_t color_, uint16_t fon_, char *str_, Ssd1289::sFont *f, uint8_t interval_);
	Sstring (uint16_t x_, uint16_t y_, uint16_t color_, uint16_t fon_, uint8_t n, Ssd1289::sFont *f, uint8_t interval_);
	void setElement (uint8_t n, char val);
	void setFont (Ssd1289::sFont *f);
	void copy (const char *);
	~Sstring ();
	void draw () const override;
	void setPosition (uint16_t, uint16_t) override;
};

#endif
