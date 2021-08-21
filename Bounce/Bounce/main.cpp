#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "RenderWindow.h"
#include "Rect.h"
#include "Text.h"
#include "Collision.h"

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	int w, h;
	float spdX = .1f;
	float spdY = .05f;
	RenderWindow window("Bounce", 1280, 720);
	SDL_Texture* startTexture = window.loadFont("res/arial.ttf", "Press any key to start", 25);
	SDL_QueryTexture(startTexture, NULL, NULL, &w, &h);
	Text Start(startTexture, window.center(1280, w), window.center(720, h), w, h);
	Rect ball(window.center(1280, 16), window.center(720, 16), 16, 16);
	Rect P1(50, window.center(720, 96));
	Rect P2(1214, window.center(720, 96));

	bool gameRunning = true;
	bool start = false;
	SDL_Event event;

	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}
			if (event.type == SDL_KEYDOWN && !start) {
				start = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_UP && P1.getY() != 0) {
				P1.setY(P1.getY() - 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && P1.getY() != 624) {
				P1.setY(P1.getY() + 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && P2.getY() != 0) {
				P2.setY(P2.getY() - 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && P2.getY() != 624) {
				P2.setY(P2.getY() + 6);
			}
		}
		if (start) {
			window.clear();
			ball.setX(ball.getX() + spdX);
			ball.setY(ball.getY() + spdY);
			window.renderRect(ball.getRect());
			window.renderRect(P1.getRect());
			window.renderRect(P2.getRect());
			window.display();
		}
		else {
			window.clear();
			window.renderText(Start);
			window.display();
		}

	}

	window.clean();
	SDL_Quit();

	return 0;
}