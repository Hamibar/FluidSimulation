#include <iostream>
#include "GraphicsManager.h"
#include "SimulationBox.h"
#include "Controller.h"
#include "ConfigParser.h"
#include "ConfigInitializer.h"
#include "Config.h"

int main(int argc, char* argv[]) {
	std::string path;
	if (argc == 2) {
		path = argv[1];
	}
	else {
		std::cout << "wrong command line parameters" << std::endl;
		return 0;
	}

	Config cnf = Config();
	bool is_config_file_valid = ConfigParser::parseFile(path, cnf);
	if (!is_config_file_valid) {
		return 0;
	}

	GraphicsManager* gr = ConfigInitializer::setupGraphicsManager(cnf);
	if (gr == nullptr) {
		std::cout << "wrong graphic settings" << std::endl;
		return 0;
	}
	else if (!gr->is_font_loaded) {
		return 0;
	}

	Controller* cntr = ConfigInitializer::setupController(cnf);
	if (cntr == nullptr) {
		std::cout << "wrong contoller settings" << std::endl;
		return 0;
	}

	SimulationBox* sim_box = ConfigInitializer::setupSimulationBox(cnf);
	if (sim_box == nullptr) {
		std::cout << "wrong simulation settings" << std::endl;
		return 0;
	}

	while (gr->window.isOpen()) {
		cntr->handleButtons(gr, sim_box);
		sim_box->simStep();
		gr->render(sim_box);
	}
	return 0;
}