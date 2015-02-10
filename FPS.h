#ifndef FPS_H
#define	FPS_H

#include <SDL2/SDL.h>

class FPS
{
public:
    static FPS FPSControl;

private:
    int lastTime;
    int lastFrameTime;
    int frames;
    int constFPS; //desirable fps
    int rFPS; //actual (real) fps

public:
    FPS();
    void    setFPS(int);
    bool    GetTick(); //if true, than there was a tick
    int     GetFPS();

};

#endif	/* FPS_H */


