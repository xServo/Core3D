#include "input.hpp"
//TODO bindings

void getInput(bool *quit, std::string *keyGlobal) {
    SDL_Event e;
    std::string keyPressed = *keyGlobal;
    // Process pending events
    while (SDL_PollEvent(&e) != 0) {
        // TODO handle quitting in input.cpp???
        if (e.type == SDL_QUIT) {
            *quit = true;
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_UP) {
                keyPressed = "up";
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                keyPressed = "down";
            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                keyPressed = "left";
            }
            if (e.key.keysym.sym == SDLK_RIGHT) {
                keyPressed = "right";
            }
        }
        if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_UP) {
                if (keyPressed == "up") {
                    keyPressed = "";
                }
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                if (keyPressed == "down") {
                    keyPressed = "";
                }
            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                if (keyPressed == "left") {
                    keyPressed = "";
                }
            }
            if (e.key.keysym.sym == SDLK_RIGHT) {
                if (keyPressed == "right") {
                    keyPressed = "";
                }
            }
        }

    }
    *keyGlobal = keyPressed;
}