#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vColor;


out vec3 fragmentColor;
uniform mat4 u_Perspective;
uniform mat4 u_Translate;
uniform mat4 u_Scale;
uniform mat4 u_Rotate;
uniform mat4 u_View;
void main()
{
  gl_Position = u_Perspective * u_View * u_Translate * u_Scale * u_Rotate * vec4(aPos, 1);
  // gl_Position = vec4(aPos, 1);
  fragmentColor = vColor;
}

#shader fragment
#version 330 core
in vec3 fragmentColor;
uniform vec4 u_Color;

layout(location = 0) out vec4 color;
void main() {
  color = vec4(fragmentColor.x, u_Color.z, fragmentColor.z , 1);
  // color = u_Color;
}
