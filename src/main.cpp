#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "geometry.h"
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>

int main(int argc, char **argv){
    SDL_Window *gWindow;
    SDL_Renderer *renderer;
    Application app{720, 720, Coords{0, 0}};
    bool is_running = true;

    // Creation de la fenetre
    gWindow = init("Awesome Voronoi", 720, 720);
    if (!gWindow){
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC
    if(renderer == nullptr){
        cout << SDL_GetError() << "\n";
        exit(1);
    }

    /*  GAME LOOP  */
    while (true)
    {
        // INPUTS
        is_running = handleEvent(app);
        if (!is_running)
            break;

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
        draw(renderer, app);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);

        cout << "j'affiche des trucs\n"; // TODO
    }

    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
