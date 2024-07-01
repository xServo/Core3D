#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 aNormal;


out vec3 fragmentColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_Perspective;
uniform mat4 u_Translate;
uniform mat4 u_Scale;
uniform mat4 u_Rotate;
uniform mat4 u_View;
void main()
{
  gl_Position = u_Perspective * u_View * u_Translate * u_Scale * u_Rotate * vec4(aPos, 1);
  // gl_Position = vec4(aPos, 1);
  FragPos = vec3(u_Translate * u_Scale * u_Rotate * vec4(aPos, 1.0));
  fragmentColor = vColor;
  Normal = aNormal;
}

#shader fragment
#version 330 core

in vec3 fragmentColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 u_Color; 
// uniforms TODO
vec3 lightPos = vec3(2, 2, 2);
vec3 lightColor = vec3(0.33, 0.42, 0.18); 
vec3 ambient = vec3(0.1, 0.1, 0.1);

layout(location = 0) out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Final color calculation
    vec4 color = vec4(fragmentColor.x, u_Color.y, fragmentColor.z, 1.0); 
    vec3 result = (ambient + diffuse) * color.rgb;

    // Output final color
    FragColor = vec4(result, 1.0);
}
