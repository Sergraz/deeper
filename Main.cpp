#include "Renderer.h"
#include "State.h"
#include "FPS.h"
#define SCR_W 800
#define SCR_H 600
#define SCR_D 32
int main(int argc, char* argv[]) {
    bool running = true;

    SDL_Event Event;
    SDL_Window* window;
    // Initialize SDL and the video subsystem
    SDL_Init(SDL_INIT_EVERYTHING);
    int audio_rate = 44100;
    Uint16 audio_format = MIX_DEFAULT_FORMAT; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
        printf("Unable to open audio!\n");
        exit(1);
    }
    SDL_CreateWindowAndRenderer(SCR_W, SCR_H, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &Renderer::g_renderer);
    SDL_RenderSetLogicalSize(Renderer::g_renderer, SCR_W, SCR_H);
    FPS::FPSControl.setFPS(64);
    GameState* state = new GameState();
    while (running) {
        if (FPS::FPSControl.GetTick()) {
            //events handling
            while (SDL_PollEvent(&Event)) {
                    if (Event.type == SDL_QUIT)
                        running = false;
                    else
                        state->events(&Event);
            }
            state->clean();
            state->logic();
            state->render();
            if (state->nextState == STATE_EXIT){
                running = false;
            } else if (state-> nextState == STATE_MAIN) {
                delete state;
                state = new GameState();
            }

        }
    }
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
