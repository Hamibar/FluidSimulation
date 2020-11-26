#pragma once
#include "Fluid.h"
#include <cmath>
const float PI = 3.14f;
class Source {
public:
	const int pos_X;
	const int pos_Y;
	const float power;
	const float dens_amount;
	Source();
	Source(int pos_X, int pos_Y, float power, float dens_amount);
	void addDensity(Fluid& fl);
	virtual void produce(Fluid& fl) = 0;
};

class SimpleSource : public Source {
public:
	float angle;
	SimpleSource();
	SimpleSource(int pos_X, int pos_Y, float power, float dens_amount, float angle);
	void produce(Fluid& fl);
};

class CircleSource : public Source {
public:
	float angle;
	const float rot_speed;
	CircleSource();
	CircleSource(int pos_X, int pos_Y, float power, float dens_amount, float angle, float rot_speed);
	void produce(Fluid& fl);
};