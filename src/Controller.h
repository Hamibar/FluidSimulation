#pragma once
#include "GraphicsManager.h"
#include "SimulationBox.h"
#include "SFML/Graphics.hpp"

class Controller {
public:
	void handleButtons(GraphicsManager* gr, SimulationBox* sim_box);
	Controller();
	Controller(bool is_mouse_mode_enabled, float power = 0, float dens_amount  = 0);
private:
	const bool is_mouse_mode_enabled;
	void handleMouse(GraphicsManager* gr, SimulationBox* sim_box);
	const float ms_power;
	const float ms_dens;
	int prev_cell_X;
	int prev_cell_Y;
	sf::Mouse ms;
};