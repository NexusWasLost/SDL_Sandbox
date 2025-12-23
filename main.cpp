#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    else
        std::cout << "SDL Video System Ready to go\n";

    //create a SDL window pointer
    SDL_Window* window = nullptr;
    window = SDL_CreateWindow(
        "Base SDL Window",
        150,
        150,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    //pause the window for 5 sec
    // SDL_Delay(5000);
    int mouseMoveCount = 0;

    bool windowIsRunning = true;
    while(windowIsRunning){
        SDL_Event event;
        //start the event loop
        while(SDL_PollEvent(&event)){
            //handle events
            if(event.type == SDL_QUIT){
                windowIsRunning = false;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.scancode == SDL_SCANCODE_B){
                    std::cout << "'B' key was pressed\n";
                }
                else{
                    std::cout << "A key was pressed but it is was B\n";
                }

                int numkeys;
                const Uint8* state = SDL_GetKeyboardState(&numkeys);
                //check if space bar is pressed (state[code] stores 1 if pressed or 0 if not)
                if(state[SDL_SCANCODE_SPACE]){
                    std::cout << "SpaceBar is pressed !\n";
                }
            }
        }
    }

    //destroy the window
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
