#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Text {
public:
	Text(SDL_Texture* tex_, float x_, float y_, float w_, float h_) {
		tex = tex_;
		x = x_;
		y = y_;
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = w_;
		currentFrame.h = h_;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	void setX(float x_) {
		x = x_;
	}
	void setY(float y_) {
		y = y_;
	}
	SDL_Texture* getTex() {
		return tex;
	}
	SDL_Rect getCurrentFrame() {
		return currentFrame;
	}
	void scale(float sx, float sy) {
		x *= sx;
		y *= sy;
		currentFrame.w *= sx;
		currentFrame.h *= sy;
	}
private:
	float x, y;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};