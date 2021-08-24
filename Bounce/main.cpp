#include <iostream>
#include <chrono>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderWindow.h"
#include "Rect.h"
#include "Text.h"
#include "Collision.h"
<<<<<<< HEAD
#include "Button.h"
#include "enet/enet.h"

=======
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
using namespace std::this_thread;
using namespace std::chrono;
#undef main //why does this work????
int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	enet_initialize();
	ENetHost* client;
	ENetHost* server;
	client = enet_host_create(NULL, 1, 1, 0, 0);
	ENetAddress address;
	ENetPeer* peer;
	address.port = 1298;
	float osW = 1280.0f;
	float osH = 720.0f;
	float spdX = .1;
	float spdY = .07;
	std::string inputText;
	RenderWindow window("Bounce", 1280, 720);
<<<<<<< HEAD
	Text Start = window.loadText("Press any key to go back", osW, 700);
	Text Back = window.loadText("Press Escape to go back", osW, 600);
	Text ControlP1 = window.loadText("Controls for P1: W, S", osW, 800);
	Text ControlP2 = window.loadText("Controls for P2: Up Arrow, Down Arrow", osW, 900);
	Text ControlEsc = window.loadText("Press the Escape key at anytime during a game to stop", osW, 1000);
=======
	Text Start = window.loadText("Press any key to start", osW, osH);
	Text ControlP1 = window.loadText("Controls for P1: Up Arrow, Left Arrow", osW, 800);
	Text ControlP2 = window.loadText("Controls for P2: Left Arrow, Down Arrow", osW, 900);
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
	Text GameOver = window.loadText("Game Over", osW, osH);
	Text P1Text = window.loadText("P1", 50, 35);
	Text P2Text = window.loadText("P2", osW * 2 - 50, 35);
	Text P1Win = window.loadText("Player One Wins!", osW, 800);
	Text P2Win = window.loadText("Player Two Wins!", osW, 800);
<<<<<<< HEAD
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
=======
	Rect Ball(window.center(1280, 16), window.center(720, 16), 16, 16);
	Rect P1(50, window.center(720, 96));
	Rect P2(1214, window.center(720, 96));

	bool gameRunning = true;
	bool start = false;
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
	SDL_Event event;

	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}
<<<<<<< HEAD
			switch (screen) {
			case 0:
				if (Singleplayer.buttonEvents(event) == true) {
					screen = 1;
				}
				if (Multiplayer.buttonEvents(event)) {
					screen = 6;
				}
				if (LocalMultiplayer.buttonEvents(event) == true) {
					screen = 4;
				}
				if (Instructions.buttonEvents(event) == true) {
					screen = 5;
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
				//server
				if (event.key.keysym.scancode == SDL_SCANCODE_W && P1.getY() >= 0) {
					P1.setY(P1.getY() - 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_S && P1.getY() <= (osH - P1.getH() + 2)) {
					P1.setY(P1.getY() + 6);
				}
				break;
			case 3:
				//client
				if (event.key.keysym.scancode == SDL_SCANCODE_UP && P2.getY() >= 0) {
					P2.setY(P2.getY() - 6);
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && P2.getY() <= (osH - P2.getH() - 2)) {
					P2.setY(P2.getY() + 6);
				}
				break;
			case 4:
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
			case 5:
				if (event.type == SDL_KEYDOWN) {
					screen = 0;
				}
				break;
			case 6:
				if (Host.buttonEvents(event) == true) {
					screen = 7;
				}
				if (Join.buttonEvents(event) == true) {
					screen = 8;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					screen = 0;
				}
				break;
			case 7: {
				ENetEvent Eevent;
				address.host = ENET_HOST_ANY;
				server = enet_host_create(&address, 1, 1, 0, 0);
				if (enet_host_service(server, &Eevent, 5000) > 0 && Eevent.type == ENET_EVENT_TYPE_RECEIVE) {
					screen = 2;
				}
			}
				break;
			case 8:
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
					ENetEvent Eevent;
					SDL_StopTextInput();
					enet_address_set_host(&address, inputText.c_str());
					peer = enet_host_connect(client, &address, 1, 0);
					if  (enet_host_service(client, &Eevent, 5000) > 0 && Eevent.type == ENET_EVENT_TYPE_CONNECT) {
						window.sendPacket(peer, Ball);
						screen = 2;
					}
				}
				break;
			}
			
			
=======
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				float sx = (float)event.window.data1 / osW;
				float sy = (float)event.window.data2 / osH;
				window.clear();
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
<<<<<<< HEAD
		case 2:
		case 4:
=======
		}
		if (start) {
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
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
<<<<<<< HEAD
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							screen = 0;
						}
					}
=======
				sleep_for(5s);
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
				break;
			}
			if (Ball.getX() >= osW) {
				window.clear();
				window.renderText(GameOver);
				window.renderText(P1Win);
				window.display();
<<<<<<< HEAD
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN) {
							screen = 0;
						}
					}
=======
				sleep_for(5s);
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
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
<<<<<<< HEAD
			break;
		case 3:
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
			}
			window.renderText(P1Text);
			window.renderText(P2Text);
			window.renderRect(Ball.getRect());
			window.renderRect(P1.getRect());
			window.renderRect(P2.getRect());
			break;
		case 5:
			window.renderText(Start);
			window.renderText(ControlP1);
			window.renderText(ControlP2);
			window.renderText(ControlEsc);
			break;
		case 6:
			window.renderText(MultiplayerText);
			window.renderText(Back);
			window.renderButton(Host);
			window.renderButton(Join);
			break;
		case 7:
			window.renderText(WaitForConnection);
			break;
		case 8:
			if(renderText) {
				Ip = window.loadText(inputText, osW, 800);
				renderText = false;
            }
				window.renderText(IpText);
				window.renderText(IpText2);
				window.renderText(Ip);
			break;
=======
			window.display();
		}
		else {
			window.clear();
			window.renderText(Start);
			window.renderText(ControlP1);
			window.renderText(ControlP2);
			window.display();
>>>>>>> parent of f5ece8e (Added singleplayer, main menu, and local multiplayer)
		}

	}
	window.clean();
	SDL_Quit();

	return 0;
}
