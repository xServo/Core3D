#include "Engine.hpp"

int main() {
  Engine& engine = Engine::Instance();
  engine.Init();
  /* Engine::Instance().Init(); */
}
