#include "Girl.h"
#include "Renderer.h"
template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}
Girl::~Girl() {
    SDL_DestroyTexture(texture);
}

Girl::Girl() {
    x = 0;
    y = 500;
    w = 32;
    h = 60;
    colBox.x = 0;
    colBox.y = 17;
    colBox.h = 15;
    colBox.w = 31;
    goRight = false;
    goLeft = false;
    jumpStr = 5;
    speed = 0;
    maxSpeed = 2;
    accel = 0.2;
    jumpSpeed = 0;
    health = 200;
    teleportCount = 0;
    teleporting = false;
    texture = Renderer::loadTexture("gg.png");
    auraTexture = Renderer::loadTexture("aura.png");
    rightAnim.SetAnimation(0, 0, w, h, 4, 10);
    leftAnim.SetAnimation(w*4,0,w,h,4,10);
    defaultAnim.SetAnimation(0, 0, w, h, 1, 10);
    diveAnim.SetAnimation(w*8, 0, w, h, 1, 10);
    curAnim = &defaultAnim;
}

void Girl::logic() {
    if (jumpSpeed == 0) {
        if (speed > 0) {
            speed-=0.1;
            if (speed < 0)
                speed = 0;
        } else if (speed < 0) {
            speed +=0.1;
            if (speed > 0)
                speed = 0;
        }
    }
    if (y < 500 || jumpSpeed != 0) {
        y -= jumpSpeed;
        jumpSpeed -= 0.2;
    }
    if (y > 500) {
        jumpSpeed = 0;
        y = 500;
    }

    if (goRight) {
        changeAnim(&rightAnim);
        changeSpeed (accel);
    } else if (goLeft) {
        changeAnim(&leftAnim);
        changeSpeed (accel * (-1));
    } else {
       changeAnim(&defaultAnim);
    }
    x += speed;
    if (x < 0) {
        x = 0;
        speed = 0;
    } else if (x > 800 - w) {
        x = 800 - w;
        speed = 0;
    }


}

void Girl::changeSpeed(float step) {
    speed += step;
    if (abs(speed) > maxSpeed)
        speed = sgn(speed
                    )*maxSpeed;
}

void Girl::render() {
    Entity::render();
    if (!teleporting) {
        SDL_SetTextureAlphaMod(texture, 55 + health);
    } else {
        if (teleportCount <= 128)
            SDL_SetTextureAlphaMod(texture, 55 + health - (55 + health) / 128 * teleportCount);
        else
            SDL_SetTextureAlphaMod(texture, 255/127*teleportCount);
    }
}
