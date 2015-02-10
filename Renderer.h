#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#ifndef RENDERER_H
#define	RENDERER_H

#define SCR_W 800
#define SCR_H 600
#define SCR_D 32

class Renderer
{
public:
    Renderer();
public:
    static SDL_Renderer* g_renderer;
public:
    static SDL_Surface* loadSurface(char* File);
    static SDL_Surface* createSurface(int w, int h);
    static bool blitSurface(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
    static bool blitSurface(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
    static SDL_Texture* loadTexture(char* File);
    static SDL_Texture* loadTexture(char* File, Uint32 key);
    static bool renderTextureScale(SDL_Texture* texture, int xSrc, int ySrc, int xDest, int yDest, int wSrc, int hSrc, int wDest, int hDest);
    static bool renderTextureNoScale(SDL_Texture* texture, int xSrc, int ySrc, int xDest, int yDest, int wSrc, int hSrc);
    static bool renderTexture(SDL_Texture* texture, int xDest, int yDest);
    static bool renderTexture(SDL_Texture* texture, int xSrc, int ySrc, int xDest, int yDest, int w, int h);
    static bool renderTexture(SDL_Texture* texture, bool scale);
};

#endif	/* RENDERER_H */

