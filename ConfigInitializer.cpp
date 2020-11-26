#include "ConfigInitializer.h"

Controller* ConfigInitializer::setupController(Config& cnf) {
	return new Controller(cnf.MOUSE_ENABLE, cnf.MOUSE_POWER, cnf.MOUSE_DENS);
}

GraphicsManager* ConfigInitializer::setupGraphicsManager(Config& cnf) {
	Colorizer* colorizer = setupColorizer(cnf);
	if (colorizer == nullptr) {
		std::cout << "Wrong colorizer settings" << std::endl;
		return nullptr;
	}
	GraphicsManager* gr = new GraphicsManager(cnf.SIMULATION_SIZE, colorizer, cnf.WINDOW_RESOLUTION);
	return gr;
}

SimulationBox* ConfigInitializer::setupSimulationBox(Config& cnf) {
	SimulationBox* sim_box = new SimulationBox(cnf.SIMULATION_SIZE, cnf.SIMULATION_VISC, cnf.SIMULATION_DIFF, cnf.SIMULATION_DT);
	for (auto& sp : cnf.SOURCES) {
		Source* src = setupSources(cnf, sp);
		if (src == nullptr) {
			delete sim_box;
			std::cout << "Wrong source settings" << std::endl;
			return nullptr;
		}
		sim_box->addSource(src);
	}
	return sim_box;
}

Colorizer* ConfigInitializer::setupColorizer(Config& conf) {
	Colorizer* colorizer = nullptr;
	if (conf.COLORIZER_TYPE == "BI") {
		colorizer = new BicolorColorizer(ColorRGB(conf.BI_COLORIZER_COLOR_1), ColorRGB(conf.BI_COLORIZER_COLOR_2));
	}
	else if (conf.COLORIZER_TYPE == "SIMPLE") {
		colorizer = new SimpleColorizer(ColorRGB(conf.SIMPLE_COLORIZER_COLOR));
	}
	else if (conf.COLORIZER_TYPE == "WB") {
		colorizer = new WhiteBlackColorizer(ColorRGB());
	}
	return colorizer;
}

Source* ConfigInitializer::setupSources(Config& conf, Config::SourceParam& sp) {
	Source* src = nullptr;
	if (sp.TYPE == "SIMPLE") {
		src = new SimpleSource(sp.POS_X, sp.POS_Y, sp.POWER, sp.DENS_AMOUNT, sp.START_ANGLE);
	}
	else if (sp.TYPE == "CIRCLE") {
		src = new CircleSource(sp.POS_X, sp.POS_Y, sp.POWER, sp.DENS_AMOUNT, sp.START_ANGLE, sp.ROT_SPEED);
	}
	return src;
}
