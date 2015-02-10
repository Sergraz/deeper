#include "Enemy.h"
#include "Renderer.h"
#include "Util.h"
#include <iostream>

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

Enemy::Enemy() {
    x = 0;
    y = 0;
    w = 44;
    h = 30;
    sucking = false;
    harmless = 0;
    xSpeed = 0;
    ySpeed = 0;
    alpha = 0;
    colBox.x = 0;
    colBox.y = 0;
    colBox.h = 28;
    colBox.w = 44;
    texture = Renderer::loadTexture("enemy.png");
    defaultAnim.SetAnimation(0, 0, w, h, 3, 10);
    curAnim = &defaultAnim;
}

void Enemy::logic(float xGirl, float yGirl) {
    if (harmless > 0)
        harmless --;
    if (sucking) {
        x = xGirl - 10 + rand() % 4;
        y = yGirl + rand() % 3;
        if (rand() % 120 == 0) {
            sucking = false;
            harmless = 100;
        }
    } else {
        if (rand() % 2 == 0) {
            xSpeed += ((float)(rand() % 5 - 2) / 10);
            float yStepSpeed = ((float)(rand() % 3) / 10);
            if (rand() % 3 == 0) {
                yStepSpeed = yStepSpeed * (-1);
            }
            ySpeed += yStepSpeed;
        } else {
            if (rand() % 4 == 0) {
                xSpeed += sgn(xSpeed) / 5;
                ySpeed += sgn(ySpeed) / 5;
            } else {
                if (x <= xGirl) {
                    xSpeed += (float)(rand() % 3) / 10;
                } else {
                    xSpeed -= (float)(rand() % 3) / 10;
                }
                if (y <= yGirl) {
                    ySpeed += (float)(rand() % 3) / 10;
                } else {
                    ySpeed -= (float)(rand() % 3) / 10;
                }
            }
        }
        x += xSpeed;
        y += ySpeed;
        if (x <= 0) {
            xSpeed +=0.5;
        } else if (x >= 800-w) {
            xSpeed -= 0.5;
        }
        if (y <= 0) {
            ySpeed +=0.5;
        } else if (y >= 500-h) {
            ySpeed -= 0.5;
        }
    }
}


void Enemy::render(bool teleporting) {
    Entity::render();
    if (teleporting)
        SDL_SetTextureAlphaMod(texture, alpha);
}
