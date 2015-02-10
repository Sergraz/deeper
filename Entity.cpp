#include "Entity.h"
void Entity::render ()
{
    curAnim->NextFrame();
}

void Entity::logic ()
{
//
}

void Entity::changeAnim(Animation* newAnim)
{
    if (curAnim != newAnim)
    {
        curAnim->curFrame = 0;
        curAnim->delayCounter = 0;
        curAnim = newAnim;
    }
}

float Entity::realX()
{
    return x + colBox.x;
}

float Entity::realY()
{
    return y + colBox.y;
}

void Entity::collision (Entity *otherEntity)
{

}

Entity::~Entity() {
    SDL_DestroyTexture(texture);
}

bool Entity::isColliding(Entity *otherEntity)
{
    bool xCollides = false;
    bool yCollides = false;
    if ((realX() <= (*otherEntity).realX() && realX() + colBox.w >= (*otherEntity).realX()) ||
            (realX() >= (*otherEntity).realX() && realX() <= (*otherEntity).realX() + (*otherEntity).colBox.w))
    {
        xCollides = true;
    }
    if ((realY() <= (*otherEntity).realY() && realY() + colBox.h >= (*otherEntity).realY()) ||
            (realY() >= (*otherEntity).realY() && realY() <= (*otherEntity).realY() + (*otherEntity).colBox.h))
    {
        yCollides = true;
    }
    return xCollides && yCollides;
}
