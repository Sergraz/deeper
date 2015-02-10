
#ifndef ENTITY_H
#define	ENTITY_H
#include "Animation.h"
#include <string>
#include <SDL2/SDL.h>

class Entity {
public:
    unsigned int id;
    SDL_Texture* texture;
    //position on screen
    float x;
    float y;
    float realX();
    float realY();
    int w;
    int h;
    std::string name;
    SDL_Rect colBox; //collision box
    //int curAnim; //current animation id
    Animation *curAnim;
    Animation defaultAnim;
    void logic();
    virtual void render();
    void changeAnim(Animation*);
    bool isColliding(Entity *otherEntity);
    void collision(Entity *otherEntity);
    virtual ~Entity();
};

#endif	/* ENTITY_H */

