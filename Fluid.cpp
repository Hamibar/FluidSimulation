#include "Fluid.h"
int Fluid::size() {
	return _size;
}

Fluid::Fluid(): _size(0), viscosity(0), diffusion(0) {
	initVectors();
}

Fluid::Fluid(int size, float viscosity, float diffusion): _size(size), viscosity(viscosity), diffusion(diffusion) {
	initVectors();
}

void Fluid::initVectors() {
	vx = mtxFl(_size, std::vector<float>(_size, 0));
	vx0 = mtxFl(_size, std::vector<float>(_size, 0));
	vy = mtxFl(_size, std::vector<float>(_size, 0));
	vy0 = mtxFl(_size, std::vector<float>(_size, 0));
	density = mtxFl(_size, std::vector<float>(_size, 0));
	density0 = mtxFl(_size, std::vector<float>(_size, 0));
}
