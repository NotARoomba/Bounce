#pragma once
#include <iostream>
#include <SDL.h>


class Button {
public:
	Button(SDL_Texture* tex_, float x_, float y_, float w_, float h_) {
        tex = tex_;
        button.x = x_;
        button.y = y_;
        button.w = w_;
        button.h = h_;
	}

    bool buttonEvents(SDL_Event &event) {

        int x = 0, y = 0;

        if (event.type == SDL_MOUSEMOTION) {
            x = event.motion.x;
            y = event.motion.y;

            if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h)) {
                clip = 1;
            }

            else {
                clip = 0;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                x = event.button.x;
                y = event.button.y;

                if ((x > button.x) && (x < button.x + button.w) && (y > button.y) && (y < button.y + button.h)) {
                    clip = 2;
                    clip = 1;
                    return true;
                }
            }
        }
        return false;
    }
    float getX() {
        return button.x;
    }
    float getY() {
        return button.y;
    }
    int getW() {
        return button.w;
    }
    int getH() {
        return button.h;
    }
    float getSX() {
        return sx;
    }
    float getSY() {
        return sy;
    }
    int getClip() {
        return clip;
    }
    void setX(float x_) {
        button.x = x_;
    }
    void setY(float y_) {
        button.y = y_;
    }
    void scale(float sx_, float sy_) {
        button.x *= sx_;
        button.y *= sy_;
        button.w *= sx_;
        button.h *= sy_;
        sx = sx_;
        sy = sy_;
    }
    SDL_Texture* getTex() {
        return tex;
    }
    SDL_FRect* getButton() {
        return &button;
    }

private:
    SDL_Texture* tex;
    SDL_FRect button;
    float sx = 1, sy = 1;
    int clip = 0;
};