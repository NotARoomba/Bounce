#include <iostream>
#include <chrono>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include "RenderWindow.h"
#include "Rect.h"
#include "Text.h"
#include "Collision.h"
#include "Button.h"
using namespace std::this_thread;
using namespace std::chrono;
#undef main //darn sdl main
int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDLNet_Init();
	IPaddress ip;
	TCPsocket server = NULL;
	TCPsocket client = NULL;
	float osW = 1280.0f;
	float osH = 720.0f;
	float spdX = .1;
	float spdY = .07;
	std::string inputText;
	RenderWindow window("Bounce", 1280, 720);
	Text Start = window.loadText("Press any key to go back", osW, 700);
	Text Back = window.loadText("Press Escape to go back", osW, 600);
	Text ControlP1 = window.loadText("Controls for P1: W, S", osW, 800);
	Text ControlP2 = window.loadText("Controls for P2: Up Arrow, Down Arrow", osW, 900);
	Text ControlEsc = window.loadText("Press the Escape key at anytime during a game to stop", osW, 1000);
	Text GameOver = window.loadText("Game Over", osW, osH);
	Text P1Text = window.loadText("P1", 50, 35);
	Text P2Text = window.loadText("P2", osW * 2 - 50, 35);
	Text P1Win = window.loadText("Player One Wins!", osW, 800);
	Text P2Win = window.loadText("Player Two Wins!", osW, 800);
	Text Bounce = window.loadText("Bounce", osW, 500);
	Text MultiplayerText = window.loadText("Multiplayer", osW, 500);
	Text WaitForConnection = window.loadText("Waiting for a connection...", osW, osH);
	Text IpText = window.loadText("IP Adress of Server", osW, 700);
	Text IpText2 = window.loadText("Press Enter when done", osW, 900);
	Text Ip = window.loadText(inputText, osW, 800);
	Rect Ball(window.center(1280, 16), window.center(720, 16), 16, 16);
	Rect P1(50, window.center(720, 96));
	Rect P2(1214, window.center(720, 96));
	Button Singleplayer(window.loadTexture("res/sprites/singleplayer.png"), window.center(1280, 102), window.center(720, 52), 102, 52);
	Button Multiplayer(window.loadTexture("res/sprites/multiplayer.png"), window.center(1280, 102), window.center(820, 52), 102, 52);
	Button LocalMultiplayer(window.loadTexture("res/sprites/localMultiplayer.png"), window.center(1280, 102), window.center(920, 52), 102, 52);
	Button Instructions(window.loadTexture("res/sprites/instructions.png"), window.center(1280, 102), window.center(1020, 52), 102, 52);
	Button Quit(window.loadTexture("res/sprites/quit.png"), window.center(1280, 102), window.center(1120, 52), 102, 52);
	Button Host(window.loadTexture("res/sprites/host.png"), window.center(1280, 102), window.center(720, 52), 102, 52);
	Button Join(window.loadTexture("res/sprites/join.png"), window.center(1280, 102), window.center(820, 52), 102, 52);


	bool gameRunning = true;
	bool renderText = false;
	int screen = 0;
	SDL_Event event;

	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}
			switch (screen) {
			case 0:
				if (Singleplayer.buttonEvents(event) == true) {
					screen = 1;
				}
				if (Multiplayer.buttonEvents(event)) {
					screen = 5;
				}
				if (LocalMultiplayer.buttonEvents(event) == true) {
					screen = 3;
				}
				if (Instructions.buttonEvents(event) == true) {
					screen = 4;
				}
				if (Quit.buttonEvents(event) == true) {
					gameRunning = false;
				}
				break;
			case 1:
				if (event.key.keysym.scancode == SDL_SCANCODE_W && P1.getY() >= 0) {
					P1.setY(P1.getY() - 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_S && P1.getY() <= (osH - P1.getH() + 2)) {
					P1.setY(P1.getY() + 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					screen = 0;
				}
				break;
			case 2:
				break;
			case 3:
				if (event.key.keysym.scancode == SDL_SCANCODE_W && P1.getY() >= 0) {
					P1.setY(P1.getY() - 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_S && P1.getY() <= (osH - P1.getH() + 2)) {
					P1.setY(P1.getY() + 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_UP && P2.getY() >= 0) {
					P2.setY(P2.getY() - 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && P2.getY() <= (osH - P2.getH() - 2)) {
					P2.setY(P2.getY() + 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					screen = 0;
				}
				break;
			case 4:
				if (event.type == SDL_KEYDOWN) {
					screen = 0;
				}
				break;
			case 5:
				if (Host.buttonEvents(event) == true) {
					screen = 6;
				}
				if (Join.buttonEvents(event) == true) {
					screen = 7;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					screen = 0;
				}
				break;
			case 6: {
				server = SDLNet_TCP_Open(&ip);
				SDLNet_ResolveHost(&ip, NULL, 1298);
				client = SDLNet_TCP_Accept(server);
				if (client) {
					screen = 2;
				}
			}
				break;
			case 7:
				SDL_StartTextInput();
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
						inputText.pop_back();
						renderText = true;
					}
					else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
						SDL_SetClipboardText(inputText.c_str());
					}
					else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
						inputText = SDL_GetClipboardText();
						renderText = true;
					}
				}
				if (event.type == SDL_TEXTINPUT)
				{
					if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')))
					{
						inputText += event.text.text;
						renderText = true;
					}
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
					SDL_StopTextInput();
					std::cout << inputText.c_str();
					server = SDLNet_TCP_Open(&ip);
					if(SDLNet_ResolveHost(&ip, inputText.c_str(), 1298));
					client = SDLNet_TCP_Accept(server);
					if (client) {
						screen = 2;
					}
				}
				break;
			}
			
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				window.clear();
				float sx = (float)event.window.data1 / osW;
				float sy = (float)event.window.data2 / osH;
				Start.scale(sx, sy);
				GameOver.scale(sx, sy);
				P1Win.scale(sx, sy);
				P2Win.scale(sx, sy);
				P1Text.scale(sx, sy);
				P2Text.scale(sx, sy);
				ControlP1.scale(sx, sy);
				ControlP2.scale(sx, sy);
				ControlEsc.scale(sx, sy);
				Ball.scale(sx, sy);
				P1.scale(sx, sy);
				P2.scale(sx, sy);
				Bounce.scale(sx, sy);
				Singleplayer.scale(sx, sy);
				Multiplayer.scale(sx, sy);
				LocalMultiplayer.scale(sx, sy);
				Instructions.scale(sx, sy);
				Quit.scale(sx, sy);
				spdX *= sx;
				spdY *= sy;
				osW = event.window.data1;
				osH = event.window.data2;
				window.display();
			}
		}
		window.clear();
		switch (screen) {
		case 0:
			Ball.setX(window.center(1280, 16));
			Ball.setY(window.center(720, 96));
			P1.setX(50);
			P1.setY(window.center(720, 96));
			P2.setX(1214);
			P2.setY(window.center(720, 96));
			window.renderText(Bounce);
			window.renderButton(Singleplayer);
			window.renderButton(Multiplayer);
			window.renderButton(LocalMultiplayer);
			window.renderButton(Instructions);
			window.renderButton(Quit);
			break;
		case 1:
			if (Ball.getY() <= P2.getY() && P2.getY() >= 0) {
				P2.setY(P2.getY() - 6);
			}
			if (Ball.getY() >= P2.getY() && P2.getY() <= (osH - P2.getH() - 2)) {
				P2.setY(P2.getY() + 6);
			}
		case 3:
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
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							screen = 0;
						}
					}
				break;
			}
			if (Ball.getX() >= osW) {
				window.clear();
				window.renderText(GameOver);
				window.renderText(P1Win);
				window.display();
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							screen = 0;
						}
					}
				break;
			}
			Ball.setX(Ball.getX() + spdX);
			Ball.setY(Ball.getY() + spdY);
			window.renderText(P1Text);
			window.renderText(P2Text);
			window.renderRect(Ball.getRect());
			window.renderRect(P1.getRect());
			window.renderRect(P2.getRect());
			break;
		case 2:
			break;
		case 4:
			window.renderText(Start);
			window.renderText(ControlP1);
			window.renderText(ControlP2);
			window.renderText(ControlEsc);
			break;
		case 5:
			window.renderText(MultiplayerText);
			window.renderText(Back);
			window.renderButton(Host);
			window.renderButton(Join);
			break;
		case 6:
			window.renderText(WaitForConnection);
			break;
		case 7:
			if(renderText) {
				Ip = window.loadText(inputText, osW, 800);
				renderText = false;
            }
			if (!client) {
				window.renderText(IpText);
				window.renderText(IpText2);
				window.renderText(Ip);
			}
			else {
				window.renderText(WaitForConnection);
			}
			break;
		}
		window.display();
	}
	SDLNet_TCP_Close(server);
	if (client) {
		SDLNet_TCP_Close(client);
	}
	window.clean();
	SDL_Quit();

	return 0;
}