#pragma once
#include <vector>
#include <cmath>
#include "Fluid.h"
class Simulation {
public:
	static void makeStep(Fluid& fl, float dt);
private:
	static void solve(Fluid& fl, mtxFl& par, mtxFl& par0, int iter_count, float a, float c, char axis);
	static void diffuse(Fluid& fl, mtxFl& par, mtxFl& par0, int iter_count, float diff, char axis, float dt);
	static void advect(Fluid& fl, mtxFl& vx, mtxFl& vy, mtxFl& d, mtxFl& d0, char axis, float dt);
	static void project(Fluid& fl, mtxFl& vx, mtxFl& vy, mtxFl& p, mtxFl& div, int iter_count);
	static void handleBorder(Fluid& fl, mtxFl& par, char axis);
};

