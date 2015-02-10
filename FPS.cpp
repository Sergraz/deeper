#include "FPS.h"

FPS FPS::FPSControl;

FPS::FPS()
{
    lastTime = 0;
    lastFrameTime = 0;
    frames = 0;
    rFPS = 0; //real FPS
    constFPS = 64; //constant FPS
}

bool FPS::GetTick()
{
    int curTime;
    curTime = SDL_GetTicks();
    //на случай если программа включена больше 49 дней
    if (curTime < lastTime)
    {
        lastTime = 0;
    }
    //проверяем, прошёл ли тик (секунда/FPS)
    if (lastTime + 1000/constFPS < curTime)
    {
        //first, let's count actual fps
        frames ++;
        if (lastFrameTime + 1000 < curTime)
        {
            lastFrameTime = curTime;
            rFPS = frames;
            frames = 0;
        }
        //now about our tick
        lastTime = curTime;
        return true;
    }
    return false;
}

int FPS::GetFPS()
{
    return rFPS;
}

void FPS::setFPS(int newFPS)
{
    constFPS = newFPS;
}
