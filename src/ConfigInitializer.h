#pragma once
#include "GraphicsManager.h"
#include "Controller.h"
#include "SimulationBox.h"
#include "Config.h"
#include <iostream>

class ConfigInitializer {
public:
	static Controller* setupController(Config& cnf);
	static GraphicsManager* setupGraphicsManager(Config& cnf);
	static SimulationBox* setupSimulationBox(Config& cnf);
private:
	static Colorizer* setupColorizer(Config& conf);
	static Source* setupSources(Config& conf, Config::SourceParam& sp);
};

