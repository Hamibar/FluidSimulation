#include "Source.h"

Source::Source() : pos_X(0), pos_Y(0), power(0), dens_amount(0) {}

Source::Source(int pos_X, int pos_Y, float power, float dens_amount): pos_X(pos_X), pos_Y(pos_Y), power(power), dens_amount(dens_amount) {}

void Source::addDensity(Fluid& fl) {
	fl.density[pos_X][pos_Y] += 16 *  dens_amount;
}


CircleSource::CircleSource() : Source(), angle(0), rot_speed(0) {}

CircleSource::CircleSource(int pos_X, int pos_Y, float power, float dens_amount, float angle, float rot_speed) : 
	Source(pos_X, pos_Y, power, dens_amount), angle(angle), rot_speed(rot_speed) {}

void CircleSource::produce(Fluid& fl) {
	addDensity(fl);
	fl.vx[pos_X][pos_Y] += (float)cos(angle) * power;
	fl.vy[pos_X][pos_Y] += (float)sin(angle) * power;
	angle += rot_speed;
}

SimpleSource::SimpleSource(): Source(), angle() {}

SimpleSource::SimpleSource(int pos_X, int pos_Y, float power, float dens_amount, float angle):
	Source(pos_X, pos_Y, power, dens_amount), angle(angle){ }

void SimpleSource::produce(Fluid& fl) {
	addDensity(fl);
	fl.vx[pos_X][pos_Y] += (float)cos(angle) * power;
	fl.vy[pos_X][pos_Y] += (float)sin(angle) * power;
}