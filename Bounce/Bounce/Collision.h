#pragma once
#include <SDL.h>
#include "Rect.h"


bool collision(Rect& ball, Rect& player) {
    if (ball.getX() + ball.getW() / 2 < player.getX() - player.getW() / 2) return false;
    if (ball.getX() - ball.getW() / 2 > player.getX() + player.getW() / 2) return false;
    if (ball.getY() + ball.getH() / 2 < player.getY() - player.getH() / 2) return false;
    if (ball.getY() - ball.getH() / 2 > player.getY() + player.getH() / 2) return false;
	return true;
}