#include <iostream>
#include <SDL2/SDL.h>

void printKey(SDL_Scancode scancode);
void renderStuff(SDL_Renderer* renderer, int x, int y);
void displayRendererInfo(SDL_Renderer* renderer);
void setBrushColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

//shape drawing functions
void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
void drawHollowRect(SDL_Renderer* renderer, int x, int y, int w, int h);
void drawFilledRect(SDL_Renderer* renderer, int x, int y, int w, int h);

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
        1280,
        720,
        SDL_WINDOW_SHOWN
    );

    //create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //prints the info (name) of the graphics API context used.
    displayRendererInfo(renderer);

    //basic rectangle dimensions
    int rectX = 525, rectY = 250;

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

                //move the rectangle depending on arrows
                if(code == SDL_SCANCODE_W){
                    rectY -= 20;
                }
                else if(code == SDL_SCANCODE_S){
                    rectY += 20;
                }
                else if(code == SDL_SCANCODE_A){
                    rectX -= 20;
                }
                else if(code == SDL_SCANCODE_D){
                    rectX += 20;
                }
            }
        }
        //render frames each iteration
        renderStuff(renderer, rectX, rectY);
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

void renderStuff(SDL_Renderer* renderer, int x, int y){
    setBrushColor(renderer, 0, 255, 0, 255);

    //clear the rendering target with drawing color
    int clear = SDL_RenderClear(renderer);
    if(clear < 0){
        std::cout << "SDL Clear failed failed: " << SDL_GetError();
    }

    setBrushColor(renderer, 255, 255, 255, 255);

    //draw a simple square
    // int x = 0, y = 0, w = 0, h = 0;
    // std::cout << "Enter the dimensions of the rectangle to draw: \n";
    // std::cin >> x;
    // std::cin >> y;
    // std::cin >> w;
    // std::cin >> h;
    int w = 100, h = 100;
    drawFilledRect(renderer, x, y, w, h);

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
void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2){
    //draw line
    int lineDrew = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    if(lineDrew < 0){
        std::cout << "SDL Failed to Draw Line: " << SDL_GetError();
    }
}

void drawHollowRect(SDL_Renderer* renderer, int x, int y, int w, int h){
    //draw rectangle
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    int rectDrew = SDL_RenderDrawRect(renderer, &rect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Rectangle: " << SDL_GetError();
        return;
    }
}

void drawFilledRect(SDL_Renderer* renderer, int x, int y, int w, int h){
    //draw filled rectangle
    SDL_Rect filledRect;
    filledRect.x = x;
    filledRect.y = y;
    filledRect.w = w;
    filledRect.h = h;

    int rectDrew = SDL_RenderFillRect(renderer, &filledRect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Filled Rectangle: " << SDL_GetError();
        return;
    }
}
