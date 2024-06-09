#include <SDL.h>
#include <iostream>
#include <random>
#include "point.hpp"
#include "input.hpp"
#include "player.hpp"

bool init();
void close();
int random_range(int x,int y);
int timePassed(int& deltaTime);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
const int SCREEN_HEIGHT = 426;
const int SCREEN_WIDTH = 640;

int main() {
    if (!init()) {
        std::cerr << "Failed to initialize!\n";
    } else {
        Player player;
        bool quit = false;
        int color = 125;
        int deltaTime;
        std::string keyPressed;
        SDL_Rect rect = {SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2-50, 50, 50};
        // Initialize last frame time
        int lastFrameTime = SDL_GetTicks();
        // game loop
        while (!quit) {
            getInput(&quit, &keyPressed);
            deltaTime = timePassed(lastFrameTime);

            printf("%s", keyPressed.c_str());


            if(keyPressed == "down") {
                rect.y = rect.y + 0.05 * deltaTime;
            }
            if(keyPressed == "up") {
                rect.y = rect.y - 0.05 * deltaTime;
            }
            if(keyPressed == "left") {
                rect.x = rect.x - 0.05 * deltaTime;
            }
            if(keyPressed == "right") {
                rect.x = rect.x + 0.05 * deltaTime;
            }

            //background
            color = color + random_range(-5,5);
            if (color > 255 || color < 0) {
                color = 125;
            }
            SDL_SetRenderDrawColor(gRenderer, 255, 200, color, color); // skin color
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

            // draw test line
            SDL_RenderDrawLine(gRenderer, 50, 50, 200, 200);

            SDL_RenderPresent(gRenderer);
            SDL_Delay(32);
            printf("1 frame %i\n", deltaTime);
        }
    }

    close();
    return 0;
}

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        gWindow = SDL_CreateWindow("RYAN SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }

    return success;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    printf("exiting...\n");
    SDL_Quit();
}

// Function to generate a random integer in the range [min, max]
int random_range(int min, int max) {
    // Random device to seed the generator
    std::random_device rd;

    // Mersenne Twister pseudo-random number generator
    std::mt19937 gen(rd());

    // Uniform distribution in the range [min, max]
    std::uniform_int_distribution<int> dis(min, max);

    // Generate and return the random number
    return dis(gen);
}

int timePassed(int& last) {
    int currentTicks = SDL_GetTicks();
    int deltaTime = currentTicks - last;
    last = currentTicks;  // Update last frame time
    return deltaTime;
}