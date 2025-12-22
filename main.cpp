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
    int eventCount = 0;
    bool windowIsRunning = true;
    while(windowIsRunning){
        SDL_Event event;
        //start the event loop
        while(SDL_PollEvent(&event)){
            //handle events
            if(event.type == SDL_QUIT){
                windowIsRunning = false;
            }
            eventCount++;
            std::cout << "Event: " << eventCount  << ", Event Type: " << event.type << "\n";
        }
    }

    //destroy the window
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
