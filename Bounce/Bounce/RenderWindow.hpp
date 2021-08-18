#pragma once

#include <SDL.h>
#include <SDL_image.h>

	class RenderWindow {
	public:
		RenderWindow(const char* title, int w, int h) {
			window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		};
		void clean() {
			SDL_DestroyWindow(window);
		}
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
	};