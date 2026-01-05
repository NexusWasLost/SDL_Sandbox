#include <iostream>
#include <SDL2/SDL.h>

#define WINDOW_MAX_WIDTH 1280
#define WINDOW_MAX_HEIGHT 720
#define BOX_WIDTH 100
#define BOX_HEIGHT 100
#define FRAMERATE_CAP 60

float const target_frametime = 1000/FRAMERATE_CAP;

void printKey(SDL_Scancode scancode);
void renderStuff(SDL_Renderer* renderer, int x, int y);
void displayRendererInfo(SDL_Renderer* renderer);
void setBrushColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

//shape drawing functions
void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
void drawHollowRect(SDL_Renderer* renderer, int x, int y);
void drawFilledRect(SDL_Renderer* renderer, int x, int y);

//direction based collision detection
bool upCollision(int y);
bool downCollision(int y);
bool leftCollision(int x);
bool rightCollision(int x);

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
        WINDOW_MAX_WIDTH,
        WINDOW_MAX_HEIGHT,
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
        //get the time of the start of the frame
        Uint32 framestart = SDL_GetTicks();

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
                if(code == SDL_SCANCODE_W && !upCollision(rectY)){
                    rectY -= 20;
                }
                else if(code == SDL_SCANCODE_S && !downCollision(rectY)){
                    rectY += 20;
                }
                else if(code == SDL_SCANCODE_A && !leftCollision(rectX)){
                    rectX -= 20;
                }
                else if(code == SDL_SCANCODE_D && !rightCollision(rectX)){
                    rectX += 20;
                }
            }
        }
        //render frames each iteration
        renderStuff(renderer, rectX, rectY);

        //get the time of how long it took to render a frame (currentTime - frameStart)
        Uint32 actual_frametime = SDL_GetTicks() - framestart;
        //When done we check if the application took less than our designated time (16.6ms) if yes we wait for the rest of the time
        if(actual_frametime <= target_frametime){
            SDL_Delay(target_frametime - actual_frametime);
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

void renderStuff(SDL_Renderer* renderer, int x, int y){
    setBrushColor(renderer, 0, 255, 0, 255);

    //clear the rendering target with drawing color
    int clear = SDL_RenderClear(renderer);
    if(clear < 0){
        std::cout << "SDL Clear failed failed: " << SDL_GetError();
    }

    setBrushColor(renderer, 255, 255, 255, 255);

    drawFilledRect(renderer, x, y);

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

void drawHollowRect(SDL_Renderer* renderer, int x, int y){
    //draw rectangle
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = BOX_WIDTH;
    rect.h = BOX_HEIGHT;

    int rectDrew = SDL_RenderDrawRect(renderer, &rect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Rectangle: " << SDL_GetError();
        return;
    }
}

void drawFilledRect(SDL_Renderer* renderer, int x, int y){
    //draw filled rectangle
    SDL_Rect filledRect;
    filledRect.x = x;
    filledRect.y = y;
    filledRect.w = BOX_WIDTH;
    filledRect.h = BOX_HEIGHT;

    int rectDrew = SDL_RenderFillRect(renderer, &filledRect);
    if(rectDrew < 0){
        std::cout << "SDL Failed to Draw Filled Rectangle: " << SDL_GetError();
        return;
    }
}

bool upCollision(int y){
    if(y <= 0){
        return true;
    }
    return false;
}

bool downCollision(int y){
    if(y + BOX_HEIGHT >= WINDOW_MAX_HEIGHT){
        return true;
    }
    return false;
}

bool leftCollision(int x){
    if(x <= 0){
        return true;
    }
    return false;
}

bool rightCollision(int x){
    if(x + BOX_WIDTH >= WINDOW_MAX_WIDTH){
        return true;
    }
    return false;
}
