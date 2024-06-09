#ifndef player_hpp
#define player_hpp
#include "point.hpp"
class Player {
    public: 
        point3D position;
        float direction; // x/359
        float fov;
        Player() {
            position = {0, 0, 0};
            direction = 0.0f; // x/359
            fov = 90.0f;
        }
};
#endif