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
    int curTime = SDL_GetTicks();
    //на случай если программа включена больше 49 дней
    if (curTime < lastTime) {
        lastTime = 0;
    }
    //проверяем, прошёл ли тик (секунда/cFPS)
    int timeTest = 1000/cFPS  + lastTime - curTime;
    if (timeTest  > 0) {
        SDL_Delay(timeTest);
    }
    //first, let's count actual fps
    frames ++;
    if (lastFrameTime + 1000 < curTime) {
        lastFrameTime = curTime;
        rFPS = frames;
        frames = 0;
   //     if (g_config.debug) {
    //        if (rFPS < cFPS - 1) {
     //           smallFPSCount ++;
      //          smallFPSPool += rFPS;
       //     }
        //}
    }
    //now about our tick
    lastTime = SDL_GetTicks();
    if (lastTime < curTime - 1000/cFPS) {
        lastTime = curTime;
    }
    return true;
}

int FPS::GetFPS()
{
    return rFPS;
}

void FPS::setFPS(int newFPS)
{
    constFPS = newFPS;
}
