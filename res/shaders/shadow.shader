#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_LightSpace;
uniform mat4 u_Model;

void main() {
  gl_Position = u_LightSpace * u_Model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core


void main() {             
  // depth shader, no frag required
  // gl_FragDepth = gl_FragCoord.z; this is whats happening 
}  