#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "GameObject.hpp"
#include "Engine.hpp"

class Editor {
private:
  const std::string VERSION;

public:
  Editor(std::string VERSION);
  ~Editor();
  void UILoop();
  // void GenObject(ObjectAttrib attrib);
  // void SaveObject();
};
