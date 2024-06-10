#ifndef player_hpp
#define player_hpp
#include "point.hpp"
class Player {
    public: 
        point3D pos;
        float direction;
        float fov;
        Player() {
            pos.x = 300;
            pos.y = 300;
            pos.z = 0;
            direction = 50; // x/359
            fov = 90;
        }
};
#endif