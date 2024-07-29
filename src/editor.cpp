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
  ImGui::SetNextWindowSize(ImVec2(300, 400));
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  std::string windowTitle = "Core3D Version 0. FPS: " + std::to_string(static_cast<int>(ImGui::GetIO().Framerate));
  ImGui::Begin("Core3D Version 0");  // Create a window and append into it.
  // FPS
  int fps = static_cast<int>(ImGui::GetIO().Framerate);
  ImGui::Text("FPS: %i\n", fps);  // Display some text

  // objects
  for (auto obj : objects ) {
    /* ImGui::Text(); */ 
    std::string title = obj -> name + ":";
    if (ImGui::CollapsingHeader(title.c_str())) {
      /* attributes */ 
      /* pos */
      glm::vec3 pos = obj -> GetPos();
      static glm::vec3 s_Pos = pos;
      static float xPos = pos.x;
      static float yPos = pos.y;
      static float zPos = pos.z;
      /* color */ 
      static glm::vec3 color = obj -> GetColor();
      /* pos sliders */ 
      bool b1 = ImGui::SliderFloat("x pos", &xPos, s_Pos.x - 1.0f, s_Pos.x + 1.0f);
      bool b2 = ImGui::SliderFloat("y pos", &yPos, s_Pos.y - 1.0f, s_Pos.y + 1.0f);
      bool b3 = ImGui::SliderFloat("z pos", &zPos, s_Pos.z - 1.0f, s_Pos.z + 1.0f);
      if (b1 || b2 || b3) {
        obj -> SetPos(glm::vec3(xPos, yPos, zPos));
      }
      /* color picker */
      if (ImGui::ColorPicker3("Pick a color", &color.x, ImGuiColorEditFlags_NoInputs)) {
        obj -> Color(color);
        std::cout << "bulb moved" << std::endl;
      }
    }
  }

  ImGui::End();
}
