#pragma once
#include <string>
#include <fstream>
#include "Config.h"
#include <iostream>
#include <fstream>

class ConfigParser {
public:
	static bool parseFile(std::string& file_name, Config& cnf);
private:
	static bool parseGraphicParam(std::ifstream& is, Config& cnf);
	static bool parseSimParam(std::ifstream& is, Config& cnf);
	static bool parseControllerParam(std::ifstream& is, Config& cnf);
	static bool parseSource(std::ifstream& is, Config& cnf);
	static bool handleOpenBracket(std::ifstream& is);
	static void wrongParamMess(std::string& param_name);
	static void wrongBlockMess(std::string& block_name);
};



