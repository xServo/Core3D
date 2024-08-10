#include "Engine.hpp"
#include <string>
std::string VERSION = "0";

int main() {
  std::cout << "Core3D Version: " << VERSION << std::endl;
  Engine &engine = Engine::Instance();
  engine.Init();
}
