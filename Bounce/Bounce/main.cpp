#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.hpp"

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	RenderWindow window("Bounce", 1280, 720);
	bool gameRunning = true;
	SDL_Event event;
	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}
		}

	}

	window.clean();
	SDL_Quit();

	return 0;
}