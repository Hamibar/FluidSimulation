#pragma once
#include <string>
#include <vector>
struct Config {
	struct SourceParam {
		std::string TYPE;
		int POS_X;
		int POS_Y;
		float POWER;
		float DENS_AMOUNT;
		float START_ANGLE;
		float ROT_SPEED;
		SourceParam() : TYPE("SIMPLE"), POS_X(0), POS_Y(0), POWER(0), DENS_AMOUNT(0), START_ANGLE(0), ROT_SPEED(0){}
	};

	std::string COLORIZER_TYPE;
	float WINDOW_RESOLUTION;
	int BI_COLORIZER_COLOR_1[3];
	int BI_COLORIZER_COLOR_2[3];
	int SIMPLE_COLORIZER_COLOR[3];

	int SIMULATION_SIZE;
	float SIMULATION_VISC;
	float SIMULATION_DIFF;
	float SIMULATION_DT;

	std::vector<SourceParam> SOURCES;

	bool MOUSE_ENABLE;
	float MOUSE_POWER;
	float MOUSE_DENS;

	Config() :
		WINDOW_RESOLUTION(2), COLORIZER_TYPE("SIMPLE"), BI_COLORIZER_COLOR_1{ 0, 0, 0 }, BI_COLORIZER_COLOR_2{ 0,0,0 }, SIMPLE_COLORIZER_COLOR{ 0,0,0 },
		SIMULATION_SIZE(200), SIMULATION_VISC(0), SIMULATION_DIFF(0), SIMULATION_DT(1),
		MOUSE_ENABLE(false), MOUSE_POWER(0), MOUSE_DENS(0)
	{
		SOURCES = std::vector<SourceParam>();
	}

	void addSourcePar() {
		SOURCES.push_back(Config::SourceParam());
	}
};
