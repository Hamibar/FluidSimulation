#include "GraphicsManager.h"

void GraphicsManager::render(SimulationBox* sim_box) {
	sf::Uint8* beg = pixels;
	for (int y = 0; y < sim_box->fl.size(); ++y) {
		for (int x = 0; x < sim_box->fl.size(); ++x) {
			int d = (int)sim_box->fl.density[x][y];
			if (d > 255) { d = 255; }
			colorizer->colorize(beg, d);
			beg += 4;
		}
	}
	window.clear();
	updateFpsInfo();
	texture->update(pixels);
	window.draw(*sprite);
	renderInfo(sim_box->total_sim_time, sim_box->fl.viscosity, sim_box->fl.diffusion);
	window.display();
}

GraphicsManager::GraphicsManager():
	info_panel_len(0), size(0), fps_buffer_size(30), fps(0), resolution(0),
	window(sf::VideoMode(size, size), "Fluid Simulation!", (!sf::Style::Resize) | sf::Style::Close),
	font(sf::Font()), is_font_loaded(false)
{
	time_points = std::vector<std::chrono::system_clock::time_point>();
	time_points.push_back(std::chrono::system_clock::now());
	colorizer = new SimpleColorizer();
	pixels = new sf::Uint8[size * size * 4];
	texture = new sf::Texture();
	texture->create(size, size);
	sprite = new sf::Sprite(*texture);
	window.display();
}

GraphicsManager::GraphicsManager(int size, Colorizer* colorizer, float resolution) : 
		info_panel_len(80), size(size), fps_buffer_size(30), fps(0), resolution(resolution), colorizer(colorizer),
		is_font_loaded(true)
{
	if (!font.loadFromFile("RobotoSlabRegular.ttf")) { is_font_loaded = false; }
	window.create(sf::VideoMode(size * resolution + info_panel_len * resolution, size * resolution),
				 "Fluid Simulation!", 
				 (!sf::Style::Resize) | sf::Style::Close);
	sf::View gameView(sf::FloatRect(0, 0, size + info_panel_len, size));
	window.setView(gameView);
	pixels = new sf::Uint8[size * size * 4];
	texture = new sf::Texture();
	texture->create(size, size);
	sprite = new sf::Sprite(*texture);
	window.display();
}

GraphicsManager::~GraphicsManager() {
	delete[] pixels;
	delete texture;	
	delete sprite;
	delete colorizer;
}

void GraphicsManager::renderInfo(float total_sim_time, float visc, float diff) {
	sf::Vertex h_line[] =
	{
		sf::Vertex(sf::Vector2f(size, 0)),
		sf::Vertex(sf::Vector2f(size, size))
	};
	window.draw(h_line, 2, sf::Lines);

	renderText(12, { size + 5.0f, 20 }, "FPS:");
	renderText(12, { size + 40.0f, 20 }, std::to_string(fps));

	renderText(12, { size + 5.0f, 50 }, "Time:");
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << total_sim_time;
	renderText(12, { size + 40.0f, 50 }, ss.str());

	renderText(12, { size + 5.0f, 80 }, "Viscosity:");
	ss.str("");
	ss << std::fixed << std::setprecision(9) << visc;
	renderText(12, { size + 5.0f, 95 }, ss.str());

	renderText(12, { size + 5.0f, 125 }, "Diffusion:");
	ss.str("");
	ss << std::fixed << std::setprecision(9) << diff;
	renderText(12, { size + 5.0f, 140 }, ss.str());

}

void GraphicsManager::renderText(int fontSize, sf::Vector2f pos, std::string mas) {
	sf::Text text;
	text.setFont(font);
	text.setString(mas);
	text.setPosition(pos);
	text.setCharacterSize(fontSize);
	window.draw(text);
}

void GraphicsManager::updateFpsInfo() {
	auto now = std::chrono::system_clock::now();
	if (time_points.size() < fps_buffer_size) { time_points.push_back(now); }
	else {
		std::rotate(time_points.begin(), time_points.begin() + 1, time_points.end());
		time_points[fps_buffer_size - 1] = now;
		std::chrono::duration<float> elapsed = time_points.back() - time_points.front();
		float avTime = elapsed.count() / time_points.size();
		fps = (int)(1.0f * time_points.size() / elapsed.count());
	}
}
