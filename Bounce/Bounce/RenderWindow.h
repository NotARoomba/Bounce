#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Rect.h"
#include "Text.h"

	class RenderWindow {
	public:
		RenderWindow(const char* title, int w, int h) {
			window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
		SDL_Texture* loadTexture(const char* filePath) {
			SDL_Texture* texture = NULL;
			texture = IMG_LoadTexture(renderer, filePath);
			
			return texture;
		}
		SDL_Texture* loadFont(const char* filePath, const char* t, int s) {
			SDL_Color color = {230, 230, 230};
			TTF_Font* font = TTF_OpenFont(filePath, s);
			SDL_Surface* surface = TTF_RenderText_Solid(font, t, color);
			SDL_Texture* texture = NULL;
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			
			return texture;
		}
		int center(int a, int b) {
			return (a - b) / 2;
		}
		void clear(){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
		}
		void renderRect(SDL_Rect* rect) {
			SDL_RenderFillRect(renderer, rect);
		}
		void renderText(Text& text) {
			SDL_Rect src, dst;
			src.x = 0;
			src.y = 0;
			src.w = text.getCurrentFrame().w;
			src.h = text.getCurrentFrame().h;
			dst.x = text.getX();
			dst.y = text.getY();
			dst.w = text.getCurrentFrame().w;
			dst.h = text.getCurrentFrame().h;

			SDL_RenderCopy(renderer, text.getTex(), &src, &dst);
		}
		void display() {
			SDL_RenderPresent(renderer);
		}
		void clean() {
			SDL_DestroyWindow(window);
		}
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
	};