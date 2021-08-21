#pragma once
#include <SDL.h>

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
	int getW() {
		return rect.w;
	}
	int getH() {
		return rect.h;
	}
	void setX(float x_) {
		rect.x = x_;
	}
	void setY(float y_) {
		rect.y = y_;
	}
	void scale(float sx, float sy) {
		rect.x *= sx;
		rect.y *= sy;
		rect.w *= sx;
		rect.h *= sy;
	}
	SDL_FRect* getRect() {
		return &rect;
	}
private:
	SDL_FRect rect;
};