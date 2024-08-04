#include "editor.hpp"

Editor::Editor() {

}

Editor::~Editor() {
  /* for (auto obj : objects) { */
  /*   delete obj; */
  /* } */
}


void Editor::UILoop() {
  /* // TODO RUN THROUGH OBJECTS AND INIT A VECTOR OF ATTRIBUTES */

  /* // Create window with name */
  /* ImGui::SetNextWindowSize(ImVec2(300, 400)); */
  /* ImGui::SetNextWindowPos(ImVec2(0, 0)); */
  /* std::string windowTitle = "Core3D Version 0. FPS: " + std::to_string(static_cast<int>(ImGui::GetIO().Framerate)); */
  /* ImGui::Begin("Core3D Version 0");  // Create a window and append into it. */
  /* // FPS */
  /* int fps = static_cast<int>(ImGui::GetIO().Framerate); */
  /* ImGui::Text("FPS: %i\n", fps);  // Display some text */

  /* std::vector<glm::vec3> colors; */
  /* // objects */
  /* int cnt = 0; */
  /* for (auto obj : objects ) { */
  /*   /1* ImGui::Text(); *1/ */ 
  /*   std::string title = obj->name + ":"; */
  /*   if (ImGui::CollapsingHeader(title.c_str())) { */
  /*     /1* attributes *1/ */ 
  /*     /1* pos *1/ */
  /*     static glm::vec3 pos = obj->GetPos(); */
  /*     /1* size *1/ */
  /*     glm::vec3 size = obj->GetSize(); */

  /*     /1* pos sliders *1/ */ 
  /*     if (ImGui::CollapsingHeader(("\tPosition:##" + obj->name).c_str())) { */
  /*       bool b1 = ImGui::SliderFloat(("x pos##" + obj->name).c_str(), &pos.x, attribMap[obj].pos.x - 1.0f, attribMap[obj].pos.x + 1.0f); */
  /*       bool b2 = ImGui::SliderFloat(("y pos##" + obj->name).c_str(), &pos.y, attribMap[obj].pos.y - 1.0f, attribMap[obj].pos.y + 1.0f); */
  /*       bool b3 = ImGui::SliderFloat(("z pos##" + obj->name).c_str(), &pos.z, attribMap[obj].pos.z - 1.0f, attribMap[obj].pos.z + 1.0f); */
  /*       if (b1 || b2 || b3) { */
  /*         obj->SetPos(glm::vec3(pos.x, pos.y, pos.z)); */
  /*         pos = obj->GetPos(); */
  /*       } */
  /*     } */
  /*     /1* scale sliders *1/ */ 
  /*     if (ImGui::CollapsingHeader(("\tScale:##" + obj->name).c_str())) { */
  /*       bool b1 = ImGui::SliderFloat(("x scale##" + obj->name).c_str(), &size.x, attribMap[obj].size.x - 1.0f, attribMap[obj].size.x + 1.0f); */
  /*       bool b2 = ImGui::SliderFloat(("y scale##" + obj->name).c_str(), &size.y, attribMap[obj].size.y - 1.0f, attribMap[obj].size.y + 1.0f); */
  /*       bool b3 = ImGui::SliderFloat(("z scale##" + obj->name).c_str(), &size.z, attribMap[obj].size.z - 1.0f, attribMap[obj].size.z + 1.0f); */
  /*       if (b1 || b2 || b3) { */
  /*         obj->SetSize(glm::vec3(size.x, size.y, size.z)); */
  /*       } */
  /*     } */
  /*     /1* color picker *1/ */
  /*     if (ImGui::ColorPicker3(("Pick a color##" + obj->name).c_str(), &attribMap[obj].color.x, ImGuiColorEditFlags_NoInputs)) { // divine intellect $color.x is just the first value in the 3 float color thing */
  /*       obj->Color(attribMap[obj].color); */
  /*     } */
  /*     cnt++; */
  /*   } */
  /* } */

  /* ImGui::End(); */
}
