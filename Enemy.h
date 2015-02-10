#ifndef ENEMY_H
#define	ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
public:
    bool sucking;
    int harmless;
    float xSpeed;
    float ySpeed;
    int alpha;
    Enemy();
    ~Enemy();
    void render(bool teleporting);
    void logic(float xGirl, float yGirl);
};

#endif	/* GIRL_H */

