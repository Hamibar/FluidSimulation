#include "Colorizer.h"

ColorRGB::ColorRGB(): r(0), g(0), b(0) {}

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}

ColorRGB::ColorRGB(int colAr[3]): r(colAr[0]), g(colAr[1]), b(colAr[2]) {}

Colorizer::Colorizer(): color(ColorRGB()) {}

Colorizer::Colorizer(ColorRGB color): color(color) {}

SimpleColorizer::SimpleColorizer(): Colorizer() {}

SimpleColorizer::SimpleColorizer(ColorRGB color): Colorizer(color) {}

void SimpleColorizer::colorize(sf::Uint8* st, uint8_t  d) {
	*st = color.r;
	*(st + 1) = color.g;
	*(st + 2) = color.b;
	*(st + 3) = d;
}

WhiteBlackColorizer::WhiteBlackColorizer(): Colorizer() {}

WhiteBlackColorizer::WhiteBlackColorizer(ColorRGB color) : Colorizer(color) {}

void WhiteBlackColorizer::colorize(sf::Uint8* st, uint8_t  d) {
	*st = d;
	*(st + 1) = d;
	*(st + 2) = d;
	*(st + 3) = 255;
}

BicolorColorizer::BicolorColorizer(): Colorizer(), end_color(ColorRGB()){}

BicolorColorizer::BicolorColorizer(ColorRGB color, ColorRGB end_color): Colorizer(color), end_color(end_color){
}

void BicolorColorizer::colorize(sf::Uint8* st, uint8_t d) {
	float df = (float)d / 255.0f;
	*st = color.r * (1.0f - df) + end_color.r * df;
	*(st + 1) = color.g * (1.0f - df) + end_color.g * df;
	*(st + 2) = color.b * (1.0f - df) + end_color.b * df;
	*(st + 3) = d;
}
