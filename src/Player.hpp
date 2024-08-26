// The player class is used for editing TODO
#include "GameObject.hpp"
#include "Camera.hpp"

class Player : public GameObject {
public:
  Camera camera;
  Player(unsigned int shader) : GameObject(shader) {
    camera.shaderID = shaderID;
    camera.Bind();
  }
};
