#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <fstream>

class Platform {
public:

	Platform();
	~Platform();
	void run();

private:

	void log_mouse_input(SDL_MouseButtonEvent* event);

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::ifstream settings_file;
	std::string window_name;
	int window_height, window_width;
	float scale_x, scale_y;
	bool running;
};
