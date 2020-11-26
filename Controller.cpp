#include "Controller.h"

void Controller::handleButtons(GraphicsManager* gr, SimulationBox* sim_box) {
	sf::Event event;
	while (gr->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gr->window.close();
		}
	}
	if (is_mouse_mode_enabled) { handleMouse(gr, sim_box); }
}

Controller::Controller(): is_mouse_mode_enabled(false), prev_cell_X(0), prev_cell_Y(0), ms_dens(0), ms_power(0) {
	ms = sf::Mouse();
}

Controller::Controller(bool is_mouse_mode_enabled, float power, float dens_ammout):
					   is_mouse_mode_enabled(is_mouse_mode_enabled), prev_cell_X(0), prev_cell_Y(0), ms_power(power), ms_dens(dens_ammout) {
	ms = sf::Mouse();
}

void Controller::handleMouse(GraphicsManager* gr, SimulationBox* sim_box) {
	float xf = ((gr->window.getSize().x - gr->info_panel_len * gr->resolution) / (float)sim_box->fl.size());
	float yf = (gr->window.getSize().y / (float)sim_box->fl.size());
	int cur_cell_X = ms.getPosition(gr->window).x / xf;
	int cur_cell_Y = ms.getPosition(gr->window).y / yf;

	if (cur_cell_X >= 2 && cur_cell_X < sim_box->fl.size() - 2 && cur_cell_Y >= 2 && cur_cell_Y < sim_box->fl.size() - 2 &&  //check borders
	   (cur_cell_X != prev_cell_X || cur_cell_Y != prev_cell_Y)) // check move
	{
		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				sim_box->fl.density[cur_cell_X + i][cur_cell_Y + j] += ms_dens;
			}
		}
		sim_box->fl.vx[cur_cell_X][cur_cell_Y] += (cur_cell_X - prev_cell_X) * ms_power;
		sim_box->fl.vy[cur_cell_X][cur_cell_Y] += (cur_cell_Y - prev_cell_Y) * ms_power;
	}
	prev_cell_X = cur_cell_X;
	prev_cell_Y = cur_cell_Y;
}
