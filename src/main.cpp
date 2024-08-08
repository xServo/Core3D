#include "Engine.hpp"
float VERSION = 0.0f;

int main() {
  std::cout << "Core3D Version: " << VERSION << std::endl;
  Engine &engine = Engine::Instance();
  engine.Init();
}
