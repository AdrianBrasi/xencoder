.PHONY: build run

link:
	cmake -S . -B build
build:
	cmake --build build
run:
	build/xencoder
