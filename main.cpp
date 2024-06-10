#include <SDL.h>
#include <iostream>
#include <random>
#include <cmath>
#include "point.hpp"
#include "input.hpp"
#include "player.hpp"

bool init();
void close();
void drawMap2D();
void drawPlayer(point3D pos);
float distance(float aX, float aY, float bX, float bY);
void rayCast(float theta);

int random_range(int x,int y);
int timePassed(int& deltaTime);
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 640;

Player player;
int mapSize = 8;
int unitY = SCREEN_HEIGHT/mapSize;
int unitX = SCREEN_WIDTH/mapSize;
int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1};


int main() {
    if (!init()) {
        std::cerr << "Failed to initialize!\n";
    } else {
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
                player.pos.y += 0.05 * deltaTime;
            }
            if(keyPressed == "up") {
                player.pos.y -= 0.05 * deltaTime;
            }
            if(keyPressed == "left") {
                player.pos.x -= 0.05 * deltaTime;
            }
            if(keyPressed == "right") {
                player.pos.x += 0.05 * deltaTime;
            }

            //background
            color = color + random_range(-5,5);
            if (color > 255 || color < 0) {
                color = 125;
            }
            SDL_SetRenderDrawColor(gRenderer, 255, 100, color, color); // skin color
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // white

            drawMap2D();
            drawPlayer(player.pos);
            player.direction += 1;
            rayCast(player.direction);
            // draw test line
            // SDL_RenderDrawLine(gRenderer, 50, 50, 200, 200);

            SDL_RenderPresent(gRenderer);
            SDL_Delay(32);
            printf("1 frame %i x:%f y:%f\n", deltaTime, player.pos.y, player.pos.y);
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

void drawMap2D() {
    int gap = 1;
    int pos = 0;
    SDL_Rect box = {0,0,unitX-gap,unitY-gap};
    for (int i=0;i<mapSize;i++) {
        for (int j=0;j<mapSize;j++) {
            if(map[pos] == 0) {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // white
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0); // black
            }
            SDL_RenderFillRect(gRenderer, &box);
            box.x+=unitX;
            pos+=1;
        }
        box.y+=unitY;
        box.x=0;
    }

}
void drawPlayer(point3D pos) {
    SDL_Rect box = {pos.x, pos.y, 12, 12};
    SDL_SetRenderDrawColor(gRenderer, 0, 100, 23, 90); // green
    SDL_RenderFillRect(gRenderer, &box);
}

void rayCast(float theta) {
    float pX, pY, vX, vY, hX, hY, nX, nY, dH, dV;
    if (theta >= 360) theta -= 360;
    float radians = theta * (M_PI / 180); // 0 = theta
    pX = player.pos.x/unitX;
    pY = player.pos.y/unitY;
    hX = pX;
    hY = pY;
    vX = pX;
    vY = pY;
    // HORIZONTAL LINES
    if (radians < M_PI) {       // looking down
        hY = floor(hY + 1);
        hX = pX + (hY - pY) / tan(radians);
    } else {                    // looking up
        hY = floor(hY);
        hX = pX + (hY - pY) / tan(radians);
    }   

    // VERTICAL LINES
    if (radians > M_PI / 2 && radians < (3 * M_PI) / 2) {       // looking right
        vX = floor(vX);
        vY = pY + (vX - pX) * tan(radians);
    }
    else {                                                      // looking left
        vX = floor(vX + 1);
        vY = pY + (vX - pX) * tan(radians);
    }
    

    // draw best ray
    dV = distance(pX, pY, vX, vY);
    dH = distance(pX, pY, hX, hY);
    SDL_SetRenderDrawColor(gRenderer, 0, 100, 23, 90); // green
    if (dV <= dH) {
        SDL_RenderDrawLine(gRenderer, pX*unitX+6, pY*unitY+6, vX*unitX, vY*unitY); // 6 is ~ half player
    } else {
        SDL_RenderDrawLine(gRenderer, pX*unitX+6, pY*unitY+6, hX*unitX, hY*unitY); // 6 is ~ half player
    }
    // SDL_RenderDrawLine(gRenderer, pX*unitX+6, pY*unitY+6, hX*unitX, hY*unitY); // 6 is ~ half player
    // SDL_RenderDrawLine(gRenderer, pX*unitX+6, pY*unitY+6, vX*unitX, vY*unitY); // 6 is ~ half player

}

float distance(float aX, float aY, float bX, float bY) {
    float d = sqrt((bX-aX)*(bX-aX) + (bY - aY)*(bY - aY));
    return d;
}