#include "editor.hpp"

Editor::Editor() {

}

Editor::~Editor() {

}
void Editor::AddObject(GameObject* obj) {
  objects.push_back(obj);
}

void Editor::UILoop() {
  // Create window with name
  std::string windowTitle = "Core3D Version 0. FPS: " + std::to_string(static_cast<int>(ImGui::GetIO().Framerate));
  ImGui::Begin("Core3D Version 0");  // Create a window and append into it.
  // FPS
  int fps = static_cast<int>(ImGui::GetIO().Framerate);
  ImGui::Text("FPS: %i", fps);  // Display some text

  // objects
  int i = 0;
  for (auto obj : objects ) {
    // counter
    i++;
    ImGui::Text("Object %i:", i);  // Display some text
    /* attributes */ 
    glm::vec3 pos = obj -> GetPos();
    static glm::vec3 s_Pos = pos;
    static float xPos = pos.x;
    static float yPos = pos.y;
    static float zPos = pos.z;
    /* pos sliders */ 
    ImGui::SliderFloat("x pos", &xPos, s_Pos.x - 1.0f, s_Pos.x + 1.0f);
    ImGui::SliderFloat("y pos", &yPos, s_Pos.y - 1.0f, s_Pos.y + 1.0f);
    ImGui::SliderFloat("z pos", &zPos, s_Pos.z - 1.0f, s_Pos.z + 1.0f);

    /* TODO optimize so it doesnt setpos if not moved */
    obj -> SetPos(glm::vec3(xPos, yPos, zPos));
  }

  ImGui::End();
}
