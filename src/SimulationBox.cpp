#include "SimulationBox.h"

SimulationBox::SimulationBox(): dt(dt), total_sim_time(0) {
	fl = Fluid();
	sources = std::vector<Source*>();
}

SimulationBox::SimulationBox(int size, float visc, float diff, float dt): dt(dt), total_sim_time(0) {
	fl = Fluid(size, visc, diff);
	sources = std::vector<Source*>();
}

void SimulationBox::addSource(Source* src) {
	sources.push_back(src);
}

SimulationBox::~SimulationBox() {
	for (Source* src : sources) {
		delete src;
	}
}

void SimulationBox::simStep() {
	for (Source* src : sources) {
		src->produce(fl);
	}
	Simulation::makeStep(fl, dt);
	total_sim_time += dt;
}
