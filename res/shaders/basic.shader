#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_Perspective;
void main()
{
    gl_Position = u_Perspective * vec4(aPos, 1);
    // gl_Position = vec4(aPos, 1);
}

#shader fragment
#version 330 core
uniform vec4 u_Color;

layout(location = 0) out vec4 color;
void main() {
    color = u_Color;
}