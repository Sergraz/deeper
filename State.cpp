#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "State.h"
#include "Enemy.h"

GameState::~GameState() {
    SDL_DestroyTexture(background);
    delete girl;
    Mix_HaltMusic();
    Mix_FreeMusic(music);

}

GameState::GameState() {
    levelMaxSpeed = 2;
    neededEnergy = 1000;
    world = 0;
    background = Renderer::loadTexture("back0.png");
    advice = Renderer::loadTexture("advice.png");
    girl = new Girl();
    energy = 800;
    music = Mix_LoadMUS("song0.mp3");
    Mix_VolumeMusic(40);
    Mix_PlayMusic(music, -1); //0 for 1, -1 for infinite loops
    jump = Mix_LoadWAV("jump.wav");
    Mix_VolumeChunk(jump, 50);
    death = Mix_LoadWAV("death.wav");
    Mix_VolumeChunk(death, 50);
    tp = Mix_LoadWAV("tp.wav");
    Mix_VolumeChunk(tp, 50);
    //enemies.front()->sucking = true;
}

void GameState::render() {
    SDL_SetRenderDrawColor(Renderer::g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(Renderer::g_renderer);
    if (girl->teleporting) {
        SDL_SetTextureAlphaMod(background2, girl->teleportCount);
        SDL_SetTextureAlphaMod(background, 255 - girl->teleportCount);

    }
    Renderer::renderTexture(background, true);
    if (girl->teleporting) {
        Renderer::renderTexture(background2, true);
    }
    if (energy >= neededEnergy) {
        Renderer::renderTexture(girl->auraTexture,0,0,girl->x - 15,girl->y-30,65,84);
    }
    girl->render();
    Draw(girl);
    for (std::vector<Enemy*>::iterator itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy ++) {
        (*itEnemy)->render(girl->teleporting);
        if (world == 4) {
            SDL_SetTextureColorMod((*itEnemy)->texture, rand()% 256, rand()% 256, rand()% 256);
        }
        Draw(*itEnemy);
    }
    if (girl->teleporting) {
        for (std::vector<Enemy*>::iterator itEnemy = newEnemies.begin(); itEnemy != newEnemies.end(); itEnemy ++) {
            if (world == 4) {
                SDL_SetTextureColorMod((*itEnemy)->texture, rand()% 256, rand()% 256, rand()% 256);
            }
            (*itEnemy)->render(girl->teleporting);
            Draw(*itEnemy);
        }
    }
    //energy = 1500;
    if (energy >= neededEnergy && world == 0 && !girl->teleporting) {
        Renderer::renderTexture(advice, 600, 40);
    }
    SDL_RenderPresent(Renderer::g_renderer);

}

void GameState::clean() {

}

void GameState::logic() {
    if (girl->goLeft && girl->goRight) {
        if (energy >= neededEnergy && girl->y == 500 && !girl->teleporting) {
            teleport (world + 1);
        }
    }

    if (!girl->teleporting) {
        girl -> logic();
    }
    for (std::vector<Enemy*>::iterator itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy ++) {
        (*itEnemy)->logic(girl->x, girl->y);
    }
    if (girl->teleporting) {
        for (std::vector<Enemy*>::iterator itEnemy = newEnemies.begin(); itEnemy != newEnemies.end(); itEnemy ++) {
            (*itEnemy)->logic(girl->x, girl->y);
        }
    }
    if (!girl->teleporting) {
        girl->maxSpeed = levelMaxSpeed;
        if (world != 5)
            energy++;
        if (girl -> health <= 0) {
            Mix_PlayChannel(-1, death, 0);
            nextState = STATE_MAIN;
        }
        for (std::vector<Enemy*>::iterator itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy ++) {
            if ((*itEnemy)->sucking) {
                girl->maxSpeed = 1;
                if (rand() % 2 == 0) {
                    girl->health--;
                }
            } else if ((*itEnemy) -> harmless == 0) {
                if (girl->isColliding(*itEnemy)) {
                    (*itEnemy)->sucking = true;
                }
            }
        }
    } else {
        girl->teleportCount ++;
        if (girl->teleportCount == 255) {
            girl->teleportCount = 0;
            girl->health = 200;
            girl->teleporting = false;
           // SDL_DestroyTexture(background);
            background = background2;
            SDL_SetTextureAlphaMod(background, 255);
            newEnemies.swap(enemies);
            std::vector<Enemy*>().swap(newEnemies);
        }
        for (std::vector<Enemy*>::iterator itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy ++) {
            (*itEnemy)->alpha = 255 - girl->teleportCount;
        }
        for (std::vector<Enemy*>::iterator itEnemy = newEnemies.begin(); itEnemy != newEnemies.end(); itEnemy ++) {
            (*itEnemy)->alpha = girl->teleportCount;
        }
    }
}

void GameState::teleport (int whereTo) {
    energy = 0;
    Mix_PlayChannel(-1, tp, 0);
    for (std::vector<Enemy*>::iterator itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy ++) {
        (*itEnemy)->sucking = false;
    }
    girl->teleporting = true;
    girl->changeAnim(&(girl->diveAnim));
    world = whereTo;
    switch (whereTo) {
        case 1:
            //SDL_DestroyTexture(background2);
            background2 = Renderer::loadTexture("back1.png");
            Mix_HaltMusic();
            Mix_FreeMusic(music);
            Mix_VolumeMusic(40);
            music = Mix_LoadMUS("song1.mp3");
            Mix_PlayMusic(music, -1);
            for (int i = 0; i < 3; i++) {
                Enemy* enemy = new Enemy();
                enemy->x = rand() % 800 - enemy->w;
                enemy->y = rand() % 300 - enemy->h;
                newEnemies.push_back(enemy);
            }
            break;
        case 2:
            //SDL_DestroyTexture(background2);
            background2 = Renderer::loadTexture("back2.png");
            girl->accel = 1;
            girl->maxSpeed = 4;
            levelMaxSpeed = 4;
            for (int i = 0; i < 6; i++) {
                Enemy* enemy = new Enemy();
                enemy->x = rand() % 800 - enemy->w;
                enemy->y = rand() % 300 - enemy->h;
                SDL_SetTextureColorMod(enemy->texture, 120, 120, 255);
                newEnemies.push_back(enemy);
            }
            break;
        case 3:
            //SDL_DestroyTexture(background2);
            background2 = Renderer::loadTexture("back3.png");
            girl->maxSpeed = 2;
            levelMaxSpeed = 2;
            girl->accel = 0.2;
            girl->jumpStr = 10;
            for (int i = 0; i < 5; i++) {
                Enemy* enemy = new Enemy();
                enemy->x = rand() % 800 - enemy->w;
                enemy->y = rand() % 300 - enemy->h;
                newEnemies.push_back(enemy);
            }
            break;
        case 4:
            //SDL_DestroyTexture(background2);
            background2 = Renderer::loadTexture("back4.png");
            girl->jumpStr = 5;
            for (int i = 0; i < 4; i++) {
                Enemy* enemy = new Enemy();
                enemy->x = rand() % 800 - enemy->w;
                enemy->y = rand() % 300 - enemy->h;
                newEnemies.push_back(enemy);
            }
            break;
        case 5:
            //SDL_DestroyTexture(background2);
            background2 = Renderer::loadTexture("further.png");
            break;
    }
    SDL_SetTextureBlendMode(background2, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background2, 0);
}

void GameState::OnKeyDown(SDL_Scancode code)
{
    switch(code){
    case SDL_SCANCODE_UP:
        if (girl->y == 500 && !girl->teleporting) {
            girl->jumpSpeed = girl->jumpStr;
            Mix_PlayChannel(-1, jump, 0);
        }
        break;
    case SDL_SCANCODE_DOWN:
        break;
    case SDL_SCANCODE_LEFT:
        girl->goLeft = true;
        break;
    case SDL_SCANCODE_RIGHT:
        girl->goRight = true;
        break;
    case SDL_SCANCODE_SPACE:

        break;
    case SDL_SCANCODE_F1:
        break;
    case SDL_SCANCODE_F2:
        break;
    case SDL_SCANCODE_ESCAPE:
        nextState = STATE_EXIT;
        break;
    case SDL_SCANCODE_1:
        break;
    case SDL_SCANCODE_2:
        break;
    case SDL_SCANCODE_V:
        break;
    case SDL_SCANCODE_C:
        break;
    case SDL_SCANCODE_X:
        break;
    case SDL_SCANCODE_M:
        /*
        if (Mix_PausedMusic()) {
            Mix_ResumeMusic();
        } else {
            Mix_PauseMusic();
        }*/
        break;
    default:
        break;
    };
}

void GameState::OnKeyUp(SDL_Scancode code) {
    switch(code){
        case SDL_SCANCODE_UP:
            if (girl->jumpSpeed > 0)
                girl->jumpSpeed = 0;
            break;
        case SDL_SCANCODE_DOWN:
            break;
        case SDL_SCANCODE_LEFT:
            girl->goLeft = false;
            break;
        case SDL_SCANCODE_RIGHT:
            girl->goRight = false;
            break;
    }
}

//draw entity on screen
void GameState::Draw(Entity *getEntity) {
    Renderer::renderTexture((*getEntity).texture,
                            (*getEntity).curAnim->XNow(),
                            (*getEntity).curAnim->YNow(),
                            (*getEntity).x,
                            (*getEntity).y,
                            (*getEntity).curAnim->w,
                            (*getEntity).curAnim->h);
}

void GameState::events(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_WINDOWEVENT:
    {
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_ENTER:
        {
            OnMouseFocus();
            break;
        }
        case SDL_WINDOWEVENT_LEAVE:
        {
            OnMouseBlur();
            break;
        }
        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
            OnInputFocus();
            break;
        }
        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
            OnInputBlur();
            break;
        }
//                case SDL_APPACTIVE: {
//                    if (event->active.gain) OnRestore();
//                    else OnMinimize();
//
//                    break;
//                }
        }
        break;
    }

    case SDL_KEYDOWN:
    {
        OnKeyDown(event->key.keysym.scancode);
        break;
    }

    case SDL_KEYUP:
    {
        OnKeyUp(event->key.keysym.scancode);
        break;
    }

    case SDL_MOUSEMOTION:
    {
        OnMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel, (event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
        break;
    }

    case SDL_MOUSEBUTTONDOWN:
    {
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
        {
            OnLButtonDown(event->button.x, event->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            OnRButtonDown(event->button.x, event->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            OnMButtonDown(event->button.x, event->button.y);
            break;
        }
        }
        break;
    }

    case SDL_MOUSEBUTTONUP:
    {
        switch (event->button.button)
        {
        case SDL_BUTTON_LEFT:
        {
            OnLButtonUp(event->button.x, event->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            OnRButtonUp(event->button.x, event->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            OnMButtonUp(event->button.x, event->button.y);
            break;
        }
        }
        break;
    }

    case SDL_JOYAXISMOTION:
    {
        OnJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
        break;
    }

    case SDL_JOYBALLMOTION:
    {
        OnJoyBall(event->jball.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
        break;
    }

    case SDL_JOYHATMOTION:
    {
        OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
        break;
    }
    case SDL_JOYBUTTONDOWN:
    {
        OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
        break;
    }

    case SDL_JOYBUTTONUP:
    {
        OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
        break;
    }

    case SDL_QUIT:
    {
        OnExit();
        break;
    }

    case SDL_SYSWMEVENT:
    {
        //Ignore
        break;
    }

//        case SDL_VIDEORESIZE:
//        {
//            OnResize(event->resize.w, event->resize.h);
//            break;
//        }

//        case SDL_VIDEOEXPOSE:
//        {
//            OnExpose();
//            break;
//        }

    default:
    {
        OnUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
        break;
    }
    }
}

void GameState::OnInputFocus()
{
    //Pure virtual, do nothing
}

void GameState::OnInputBlur()
{
    //Pure virtual, do nothing
}

void GameState::OnMouseFocus()
{
    //Pure virtual, do nothing
}

void GameState::OnMouseBlur()
{
    //Pure virtual, do nothing
}

void GameState::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
    //Pure virtual, do nothing
}

void GameState::OnMouseWheel(bool Up, bool Down)
{
    //Pure virtual, do nothing
}

void GameState::OnLButtonDown(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnLButtonUp(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnRButtonDown(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnRButtonUp(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnMButtonDown(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnMButtonUp(int mX, int mY)
{
    //Pure virtual, do nothing
}

void GameState::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
    //Pure virtual, do nothing
}

void GameState::OnJoyButtonDown(Uint8 which, Uint8 button)
{
    //Pure virtual, do nothing
}

void GameState::OnJoyButtonUp(Uint8 which, Uint8 button)
{
    //Pure virtual, do nothing
}

void GameState::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
    //Pure virtual, do nothing
}

void GameState::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
    //Pure virtual, do nothing
}

void GameState::OnMinimize()
{
    //Pure virtual, do nothing
}

void GameState::OnRestore()
{
    //Pure virtual, do nothing
}

void GameState::OnResize(int w, int h)
{
    //Pure virtual, do nothing
}

void GameState::OnExpose()
{
    //Pure virtual, do nothing
}

void GameState::OnExit()
{
    //Pure virtual, do nothing
}

void GameState::OnUser(Uint8 type, int code, void* data1, void* data2)
{
    //Pure virtual, do nothing
}
