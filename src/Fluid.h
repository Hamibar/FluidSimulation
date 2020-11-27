#pragma once
#include <vector>
typedef std::vector<std::vector<float>> mtxFl;
struct Fluid {
public:
	Fluid();
	Fluid(int size, float viscosity, float diffusion);
	int size();
	float viscosity;
	float diffusion;
	mtxFl vx;
	mtxFl vx0;
	mtxFl vy;
	mtxFl vy0;
	mtxFl density;
	mtxFl density0;
private:
	void initVectors();
	int _size;
};