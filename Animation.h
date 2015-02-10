#ifndef ANIMATION_H
#define	ANIMATION_H

class Animation
{
public:
    int delayCounter;
    int xStart;
    int yStart;
    int w;
    int h;
    int curFrame; //current frame
    int maxFrame; //number of frames
    bool oscillate; //oscillate (1-2-3-2-1) or not (1-2-3-1-2-3)
    int delay;
    float bonusDelay;
    void NextFrame();
    void GoToFrame(int);
    void SetAnimation(int xStart, int yStart, int w, int h, int maxFrame, int delay);
    int XNow();
    int YNow();

};

#endif	/* ANIMATION_H */

