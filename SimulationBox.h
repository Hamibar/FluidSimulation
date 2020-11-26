#pragma once
#include <vector>
#include "Fluid.h"
#include "Source.h"
#include "Simulation.h"

class SimulationBox {
public:
	Fluid fl;
	std::vector<Source*> sources;
	SimulationBox();
	SimulationBox(int size, float visc, float diff, float dt);
	void addSource(Source* src);
	~SimulationBox();
	void simStep();
	float total_sim_time;
private:
	const float dt;
};