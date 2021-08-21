#include <iostream>
#include <chrono>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderWindow.h"
#include "Rect.h"
#include "Text.h"
#include "Collision.h"
using namespace std::this_thread;
using namespace std::chrono;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	float osW = 1280.0f;
	float osH = 720.0f;
	float spdX = .1;
	float spdY = .07;
	RenderWindow window("Bounce", 1280, 720);
	Text Start = window.loadText("Press any key to start", osW, osH);
	Text ControlP1 = window.loadText("Controls for P1: Up Arrow, Left Arrow", osW, 800);
	Text ControlP2 = window.loadText("Controls for P2: Left Arrow, Down Arrow", osW, 900);
	Text GameOver = window.loadText("Game Over", osW, osH);
	Text P1Text = window.loadText("P1", 50, 35);
	Text P2Text = window.loadText("P2", osW * 2 - 50, 35);
	Text P1Win = window.loadText("Player One Wins!", osW, 800);
	Text P2Win = window.loadText("Player Two Wins!", osW, 800);
	Rect Ball(window.center(1280, 16), window.center(720, 16), 16, 16);
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
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				float sx = (float)event.window.data1 / osW;
				float sy = (float)event.window.data2 / osH;
				window.clear();
				Start.scale(sx, sy);
				GameOver.scale(sx, sy);
				P1Win.scale(sx, sy);
				P2Win.scale(sx, sy);
				Ball.scale(sx, sy);
				P1.scale(sx, sy);
				P2.scale(sx, sy);
				spdX *= sx;
				spdY *= sy;
				osW = event.window.data1;
				osH = event.window.data2;
				window.display();
			}
			if (event.type == SDL_KEYDOWN && !start) {
				start = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_UP && P1.getY() >= 0) {
				P1.setY(P1.getY() - 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && P1.getY() <= (osH - P1.getH())) {
				P1.setY(P1.getY() + 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && P2.getY() >= 0) {
				P2.setY(P2.getY() - 6);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && P2.getY() <= (osH  - P2.getH())) {
				P2.setY(P2.getY() + 6);
			}
		}
		if (start) {
			if (collision(Ball, P1) || collision(Ball, P2)) {
				spdX *= -1;
			}
			if ((Ball.getY() + Ball.getH()) >= osH || Ball.getY() <= 0) {
				spdY *= -1;
			}
			if (Ball.getX() <= 0) {
				window.clear();
				window.renderText(GameOver);
				window.renderText(P2Win);
				window.display();
				sleep_for(5s);
				break;
			}
			if (Ball.getX() >= osW) {
				window.clear();
				window.renderText(GameOver);
				window.renderText(P1Win);
				window.display();
				sleep_for(5s);
				break;
			}
			window.clear();
			Ball.setX(Ball.getX() + spdX);
			Ball.setY(Ball.getY() + spdY);
			window.renderText(P1Text);
			window.renderText(P2Text);
			window.renderRect(Ball.getRect());
			window.renderRect(P1.getRect());
			window.renderRect(P2.getRect());
			window.display();
		}
		else {
			window.clear();
			window.renderText(Start);
			window.renderText(ControlP1);
			window.renderText(ControlP2);
			window.display();
		}

	}

	window.clean();
	SDL_Quit();

	return 0;
}