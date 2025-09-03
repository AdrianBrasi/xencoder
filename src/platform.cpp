#include "platform.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

Platform::Platform(){
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to initialize SDL subsystem" << std::endl;
		running = false;
		exit(1);
	}
	settings_file = std::ifstream("data/settings.json");
	if (!settings_file){
		std::cerr << "Couldn't read settings file. Current dir: " << std::filesystem::current_path() << std::endl;
		running = false;
		exit(1);
	}
	try {
		std::cout << "Loading settings" << std::endl;
		nlohmann::json s = nlohmann::json::parse(settings_file);
		window_name = s["name"].get<std::string>();
		window_width = s["width"].get<int>();
		window_height = s["height"].get<int>();
	} catch (const nlohmann::json::parse_error &e) {
		std::cerr << "Error reading settings file: " << e.what() << std::endl;
		running = false;
		exit(1);
	}
	std::cout << "Settings file successfully loaded" << std::endl;

	window = SDL_CreateWindow(
		window_name.c_str(), window_width, window_height, 
		SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY // | OTHER FLAGS
	);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		running = false;
		exit(1);
	}
	SDL_SetWindowResizable(window, false);
	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer) {
		std::cerr << "Failed to create renderer" << std::endl;
		running = false;
		exit(1);
	}
	SDL_SetRenderVSync(renderer, 1);
	SDL_ShowWindow(window);

	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);


	scale_x = window_width / 1600.00;
	scale_y = window_height / 900.00;
	SDL_SetRenderScale(renderer, scale_x, scale_y);

	running = true;
}

Platform::~Platform() {
	if (running == false) {
		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
}

void Platform::run() {
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
				case SDL_EVENT_KEY_DOWN:
					// keyDown(&event);
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					log_mouse_input(&event.button);
					break;
				default: break;
			}
		}

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Render();
		SDL_SetRenderScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(renderer, (27.0 / 255.0), (30.0 / 255.0), (46.0 / 255.0), 255);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}
}

void Platform::log_mouse_input(SDL_MouseButtonEvent* event) {
	std::string button_name;
	switch (event->button) {
		case SDL_BUTTON_LEFT:
			button_name = "Left";
			break;
		case SDL_BUTTON_MIDDLE:
			button_name = "Middle";
			break;
		case SDL_BUTTON_RIGHT:
			button_name = "Right";
			break;
		case SDL_BUTTON_X1:
			button_name = "Thumb 1";
			break;
		case SDL_BUTTON_X2:
			button_name = "Thumb 2";
			break;
		default:
			button_name = "Button " + std::to_string(event->button);
			break;
	}
	std::cout << button_name << " mouse button: " << event->x << ", " << event->y << std::endl;
}
