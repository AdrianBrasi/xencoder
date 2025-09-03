#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

class Platform {
public:

	Platform();
	~Platform();
	void run();

private:

	void log_mouse_input(SDL_MouseButtonEvent* event);

	ImGuiIO* io;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::ifstream settings_file;
	std::string window_name;
	int window_height, window_width;
	float scale_x, scale_y;
	bool running;
};
