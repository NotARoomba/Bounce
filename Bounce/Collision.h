#pragma once
#include <SDL.h>
#include "Rect.h"


bool collision(Rect& ball, Rect& player) {
    /*if (ball.getX() + ball.getW() / 2 < player.getX() - player.getW() / 2) return false;
    if (ball.getX() - ball.getW() / 2 > player.getX() + player.getW() / 2) return false;
    if (ball.getY() + ball.getH() / 2 < player.getY() - player.getH() / 2) return false;
    if (ball.getY() - ball.getH() / 2 > player.getY() + player.getH() / 2) return false;
	return true;
    */

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    leftA = ball.getX();
    rightA = ball.getX() + ball.getW();
    topA = ball.getY();
    bottomA = ball.getY() + ball.getH();


    leftB = player.getX();
    rightB = player.getX() + player.getW();
    topB = player.getY();
    bottomB = player.getY() + player.getH();
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}