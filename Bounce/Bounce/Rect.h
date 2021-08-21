#pragma once
#include <SDL.h>
#include <ma>

class Rect {
public:
	Rect(float x_, float y_, float w_ = 16, float h_ = 96) {
		rect.x = x_;
		rect.y = y_;
		rect.w = w_;
		rect.h = h_;
	}
	float getX() {
		return rect.x;
	}
	float getY() {
		return rect.y;
	}
	void setX(float x_) {
		float rect.x = x_;
	}
	void setY(float y_) {
		float rect.y = y_;
	}
	SDL_Rect* getRect() {
		return &rect;
	}
private:
	SDL_Rect rect;
};