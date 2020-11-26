#pragma once
#include "SFML/Graphics.hpp"
#include "SimulationBox.h"
#include "Colorizer.h"
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>

class GraphicsManager {
public:
	void render(SimulationBox* sim_box);
	sf::RenderWindow window;
	GraphicsManager();
	GraphicsManager(int size, Colorizer* colorizer, float resolution);
	~GraphicsManager();
	const float resolution;
	const int size;
	const int info_panel_len;
	const int fps_buffer_size;
	bool is_font_loaded;
private:
	sf::Font font;
	void renderInfo(float tottal_sim_time, float visc, float diff);
	void renderText(int fontSize, sf::Vector2f pos, std::string mes);
	void updateFpsInfo();
	int fps;
	sf::Uint8* pixels;
	sf::Texture* texture;
	sf::Sprite* sprite;
	Colorizer* colorizer;
	std::vector<std::chrono::system_clock::time_point> time_points;
};