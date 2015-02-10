#ifndef GIRL_H
#define	GIRL_H

#include "Entity.h"

class Girl : public Entity
{
public:
    bool goRight;
    bool goLeft;
    int jumpStr;
    float speed;
    float maxSpeed;
    float accel;
    float jumpSpeed;
    int health;
    bool teleporting;
    int teleportCount;
    Animation leftAnim;
    Animation rightAnim;
    Animation diveAnim;
    SDL_Texture* auraTexture;
    Girl();
    ~Girl();
    void changeSpeed(float step);
    void render();
    void logic();
};

#endif	/* GIRL_H */

