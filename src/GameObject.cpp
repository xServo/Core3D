#include "GameObject.hpp"
#include "data.hpp"

GameObject::GameObject()
  : vao(positions, 8), ib(indicies, 36){
  }

void GameObject::Bind() {
  vao.Bind();
  ib.Bind();
}
void GameObject::Translate(glm::vec3 vec) {

}
GameObject::~GameObject() {

}
