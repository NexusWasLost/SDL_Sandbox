#include <iostream>
#include <SDL2/SDL.h>

void printKey(SDL_Scancode scancode);
void renderStuff(SDL_Renderer* renderer);
void displayRendererInfo(SDL_Renderer* renderer);
void setBrushColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

//shape drawing functions
void drawLine(SDL_Renderer* renderer);
void drawHollowRect(SDL_Renderer* renderer);
void drawFilledRect(SDL_Renderer* renderer);

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

    //create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //prints the info (name) of the graphics API context used.
    displayRendererInfo(renderer);
    renderStuff(renderer);

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
                SDL_Scancode code = event.key.keysym.scancode;
                printKey(code);
            }
        }
    }

    //destroy the renderer
    SDL_DestroyRenderer(renderer);
    //destroy the window
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void printKey(SDL_Scancode scancode) {
    SDL_Keycode k = SDL_GetKeyFromScancode(scancode);
    const char* pressedKey = SDL_GetKeyName(k);
    std::cout << pressedKey << "\n";
}

void displayRendererInfo(SDL_Renderer* renderer){
    SDL_RendererInfo r_info;
    int info = SDL_GetRendererInfo(renderer, &r_info);
    if(info < 0){
        std::cout << "SDL Error fetching Renderer Info: " << SDL_GetError();
        return;
    }

    std::cout << r_info.name << "\n";
}

void renderStuff(SDL_Renderer* renderer){
    setBrushColor(renderer, 255, 0, 0, 255);

    //clear the rendering target with drawing color
    int clear = SDL_RenderClear(renderer);
    if(clear < 0){
        std::cout << "SDL Clear failed failed: " << SDL_GetError();
    }

    //change the brush color to draw the line
    setBrushColor(renderer, 255, 255, 255, 255);

    // drawLine(renderer);
    drawHollowRect(renderer);
    drawFilledRect(renderer);

    //update the window
    SDL_RenderPresent(renderer);
}

void setBrushColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    int brushSetSuccess = SDL_SetRenderDrawColor(renderer, r, g, b, a);
    if(brushSetSuccess < 0){
        std::cout << "SDL Render Color Setting failed: " << SDL_GetError();
        return;
    }
}

//shape drawing functions
void drawLine(SDL_Renderer* renderer){
    //draw line
    int lineDrew = SDL_RenderDrawLine(renderer, 0, 0, 200, 200);
    if(lineDrew < 0){
        std::cout << "SDL Failed to Draw Line: " << SDL_GetError();
    }
}

void drawHollowRect(SDL_Renderer* renderer){
    //draw rectangle
    SDL_Rect rect;
    rect.x = 15;
    rect.y = 15;
    rect. w = 500;
    rect.h = 300;

    int rectDrew = SDL_RenderDrawRect(renderer, &rect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Rectangle: " << SDL_GetError();
        return;
    }
}

void drawFilledRect(SDL_Renderer* renderer){
    //draw filled rectangle
    SDL_Rect filledRect;
    filledRect.x = 60;
    filledRect.y = 60;
    filledRect. w = 400;
    filledRect.h = 200;

    int rectDrew = SDL_RenderFillRect(renderer, &filledRect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Filled Rectangle: " << SDL_GetError();
        return;
    }
}
