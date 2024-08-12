#include <string>
#include "Engine.hpp"
#include "editor.hpp"

std::string VERSION = "0";

int main() {
  std::cout << "Core3D Version: " << VERSION << std::endl;
  // init engine
  Engine& engine = Engine::Instance();

  // init editor
  Editor editor(VERSION);
  engine.SetEditorUpdateCallback([&editor]() { editor.UILoop(); });  // pass in UI loop

  // begin engine and loop
  engine.Init();
}
