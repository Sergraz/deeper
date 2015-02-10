#ifndef STATE_H
#define	STATE_H
#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"
#include "Girl.h"
#include "Enemy.h"
#include "Renderer.h"

//Game states
enum StatesId
{
    STATE_NULL,
    STATE_INTRO,
    STATE_MAIN,
    STATE_PAUSE,
    STATE_EXIT
};

//Game state base class
class GameState
{
public:
    StatesId nextState;
    StatesId stateId;

public:
    std::vector<Enemy*> enemies;
    std::vector<Enemy*> newEnemies;
    Girl* girl;
    Mix_Music* music;
    Mix_Chunk *jump = NULL;
    Mix_Chunk *death = NULL;
    Mix_Chunk *tp = NULL;
    SDL_Texture* advice;
    SDL_Texture* background;
    SDL_Texture* background2;
    int energy;
    float levelMaxSpeed;
    int neededEnergy;
    int world;
    void events(SDL_Event*);
    void clean();
    void logic();
    void render();
    void Draw(Entity*);
    void teleport(int);
    ~GameState();
    GameState();

    //events
    void OnInputFocus();
    void OnInputBlur();
    void OnKeyDown(SDL_Scancode code);
    void OnKeyUp(SDL_Scancode code);
    void OnMouseFocus();
    void OnMouseBlur();
    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
    void OnMouseWheel(bool Up, bool Down);    //Not implemented
    void OnLButtonDown(int mX, int mY);
    void OnLButtonUp(int mX, int mY);
    void OnRButtonDown(int mX, int mY);
    void OnRButtonUp(int mX, int mY);
    void OnMButtonDown(int mX, int mY);
    void OnMButtonUp(int mX, int mY);
    void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
    void OnJoyButtonDown(Uint8 which, Uint8 button);
    void OnJoyButtonUp(Uint8 which, Uint8 button);
    void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
    void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
    void OnMinimize();
    void OnRestore();
    void OnResize(int w,int h);
    void OnExpose();
    void OnExit();
    void OnUser(Uint8 type, int code, void* data1, void* data2);
};

#endif	/* STATE_H */

