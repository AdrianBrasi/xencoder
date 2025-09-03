cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(xencoder)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDLTTF_VENDORED ON)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(xencoder 
	src/main.cpp
	src/platform.h
	src/platform.cpp
)

target_link_libraries(xencoder PRIVATE 
	SDL3_ttf::SDL3_ttf 
	SDL3::SDL3 
)
