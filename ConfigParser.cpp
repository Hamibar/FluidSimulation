#include "ConfigParser.h"

bool ConfigParser::parseFile(std::string& file_name, Config& cnf) {
	std::ifstream is;
	is.open(file_name);
	if (!is.is_open()) {
		std::cout << "Error. Impossible to open file" << std::endl;
		return false;
	}
	std::string command = "";
	while (!is.eof()) {
		is >> command;
		if (command == "") { continue; }
		else if (command == "GRAPHIC" && !parseGraphicParam(is, cnf)) { return false; }
		else if (command == "SIMULATION" && !parseSimParam(is, cnf)) { return false; }
		else if (command == "CONTROLLER" &&!parseControllerParam(is, cnf)) { return false; }
		else if (command != "GRAPHIC" && command != "SIMULATION" && command != "CONTROLLER"){
			wrongBlockMess(command);
			return false;
		}
	}
	return true;
}

bool ConfigParser::parseGraphicParam(std::ifstream& is, Config& cnf) {
	std::string command;
	bool is_valid_st = handleOpenBracket(is);
	if (!is_valid_st) { return false; }
	while (command != "}" && !is.eof()) {
		is >> command;
		if (command == "COLORIZER_TYPE:") { is >> cnf.COLORIZER_TYPE; }
		else if (command == "WINDOW_RESOLUTION:") { is >> cnf.WINDOW_RESOLUTION; }
		else if (command == "BI_COLORIZER_COLOR_1:") { is >> cnf.BI_COLORIZER_COLOR_1[0]; is >> cnf.BI_COLORIZER_COLOR_1[1]; is >> cnf.BI_COLORIZER_COLOR_1[2]; }
		else if (command == "BI_COLORIZER_COLOR_2:") { is >> cnf.BI_COLORIZER_COLOR_2[0]; is >> cnf.BI_COLORIZER_COLOR_2[1]; is >> cnf.BI_COLORIZER_COLOR_2[2]; }
		else if (command == "SIMPLE_COLORIZER_COLOR:") { is >> cnf.SIMPLE_COLORIZER_COLOR[0]; is >> cnf.SIMPLE_COLORIZER_COLOR[1]; is >> cnf.SIMPLE_COLORIZER_COLOR[2]; }
		else if (command != "}"){
			wrongParamMess(command);
			return false;
		}
	}
	return true;
}

bool ConfigParser::parseSimParam(std::ifstream& is, Config& cnf) {
	std::string command;
	bool is_valid_st = handleOpenBracket(is);
	if (!is_valid_st) { return false; }
	while (command != "}" && !is.eof()) {
		is >> command;
		if (command == "SOURCE") {
			bool is_valid_source = parseSource(is, cnf);
			if (!is_valid_source) { return false; }
		}
		else if (command == "SIMULATION_SIZE:") { is >> cnf.SIMULATION_SIZE; }
		else if (command == "SIMULATION_VISC:") { is >> cnf.SIMULATION_VISC; }
		else if (command == "SIMULATION_DIFF:") { is >> cnf.SIMULATION_DIFF; }
		else if (command == "SIMULATION_DT:") { is >> cnf.SIMULATION_DT; }
		else if (command != "}") {
			wrongParamMess(command);
			return false;
		}
	}
	return true;
}

bool ConfigParser::parseControllerParam(std::ifstream& is, Config& cnf) {
	std::string command;
	bool is_valid_st = handleOpenBracket(is);
	if (!is_valid_st) { return false; }
	while (command != "}" && !is.eof()) {
		is >> command;
		if (command == "MOUSE_ENABLE:") { is >> cnf.MOUSE_ENABLE; }
		else if (command == "MOUSE_POWER:") { is >> cnf.MOUSE_POWER; }
		else if (command == "MOUSE_DENS:") { is >> cnf.MOUSE_DENS; }
		else if (command != "}") {
			wrongParamMess(command);
			return false;
		}
	}
	return true;
}

bool ConfigParser::parseSource(std::ifstream& is, Config& cnf) {
	std::string command;
	bool is_valid_st = handleOpenBracket(is);
	if (!is_valid_st) { return false; }
	cnf.addSourcePar();
	while (command != "}" && !is.eof()) {
		is >> command;
		if (command == "TYPE:") { is >> cnf.SOURCES.back().TYPE; }
		else if (command == "POS_X:") { is >> cnf.SOURCES.back().POS_X; }
		else if (command == "POS_Y:") { is >> cnf.SOURCES.back().POS_Y; }
		else if (command == "POWER:") { is >> cnf.SOURCES.back().POWER; }
		else if (command == "DENS_AMOUNT:") { is >> cnf.SOURCES.back().DENS_AMOUNT; }
		else if (command == "START_ANGLE:") { is >> cnf.SOURCES.back().START_ANGLE; }
		else if (command == "ROT_SPEED:") { is >> cnf.SOURCES.back().ROT_SPEED; }
		else if (command != "}") {
			wrongParamMess(command);
			return false;
		}
	}
	return true;
}

bool ConfigParser::handleOpenBracket(std::ifstream& is) {
	std::string command;
	is >> command;
	if (command != "{") {
		std::cout << "Block must statrs with {" << std::endl;
		return false;
	}
	return true;
}

void ConfigParser::wrongParamMess(std::string& param_name) {
	std::cout << "\"" << param_name << "\"" << " is wrong parameter name. Use readme to view available parameter names for this block" << std::endl;
}

void ConfigParser::wrongBlockMess(std::string& block_name) {
	std::cout << "\"" << block_name << "\"" << " is wrong main block name. Use readme to view available block names for this block" << std::endl;
}