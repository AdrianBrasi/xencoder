cmake_minimum_required(VERSION 3.21)
project(xencoder C CXX)
set(CMAKE_CXX_STANDARD 20)

# --- SDL core first (provides SDL3::SDL3 target)
add_subdirectory(external/SDL)

# Make sure SDL_image/ttf can see SDL's config
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/cmake")
add_subdirectory(external/SDL_image)
add_subdirectory(external/SDL_ttf)
add_subdirectory(external/nlohmann_json)

# --- Dear ImGui as a static lib with SDL3 + SDL renderer backends
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp

    external/imgui/backends/imgui_impl_sdl3.cpp
    external/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# --- Your app
add_executable(xencoder
    src/main.cpp
	src/platform.h
	src/platform.cpp
)
target_link_libraries(xencoder PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
	nlohmann_json::nlohmann_json
    imgui
)

