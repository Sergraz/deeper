#include "Animation.h"

void Animation::SetAnimation(int xStartGet, int yStartGet, int wGet, int hGet, int maxFrameGet, int delayGet)
{
    xStart = xStartGet;
    yStart = yStartGet;
    w = wGet;
    h = hGet;
    maxFrame = maxFrameGet;
    curFrame = 0;
    delay = delayGet;
    delayCounter = 0;
    bonusDelay = 1;
};

void Animation::NextFrame()
{
    if (delayCounter >= delay * bonusDelay)
    {
        if (curFrame >= maxFrame - 1)
        {
            curFrame = 0;
        }
        else
        {
            curFrame ++;
        }
        delayCounter = 0;
    }
    else
    {
        delayCounter++;
    }
};

int Animation::XNow()
{
    return (xStart + w * curFrame);
};

int Animation::YNow()
{
    return (yStart);
};
