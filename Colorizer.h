#pragma once
#include <iterator>
#include <SFML/Graphics.hpp>
#include <stdint.h>

struct ColorRGB {
	const uint8_t r;
	const uint8_t g;
	const uint8_t b;
	ColorRGB();
	ColorRGB(uint8_t r, uint8_t g, uint8_t b);
	ColorRGB(int colAr[3]);
};

class Colorizer {
public:
	Colorizer();
	Colorizer(ColorRGB color);
	virtual void colorize(sf::Uint8* st, uint8_t  d) = 0;
protected:
	const ColorRGB color;
};

class SimpleColorizer : public Colorizer {
public:
	SimpleColorizer();
	SimpleColorizer(ColorRGB color);
	void colorize(sf::Uint8* st, uint8_t  d);
};

class WhiteBlackColorizer : public Colorizer {
public:
	WhiteBlackColorizer();
	WhiteBlackColorizer(ColorRGB color);
	void colorize(sf::Uint8* st, uint8_t  d);
};

class BicolorColorizer : public Colorizer {
public:
	BicolorColorizer();
	BicolorColorizer(ColorRGB color, ColorRGB end_color);
	void colorize(sf::Uint8* st, uint8_t  d);
private:
	const ColorRGB end_color;
};

