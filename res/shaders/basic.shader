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
  mat4 model = u_Translate * u_Rotate * u_Scale;
  gl_Position = u_Perspective * u_View * model * vec4(aPos, 1);
  // gl_Position = vec4(aPos, 1);
  //FragPos = vec3(model * vec4(aPos, 1.0));
  FragPos = vec3(model * vec4(aPos, 1));
  fragmentColor = vColor;
  // Normal = mat3(transpose(inverse(model))) * aNormal;
  Normal = aNormal; 
}

#shader fragment
#version 330 core

in vec3 fragmentColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 u_Color; 
// uniforms TODO
vec3 lightPos = vec3(0, 3, 0);
vec3 lightColor = vec3(0.43, 0.52, 0.28); 
float ambientStrength = 1;
vec3 ambient = ambientStrength * lightColor;

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
    // FragColor = vec4(1, 1, 1, 1); // debug white
    // FragColor = vec4(fragmentColor.x, u_Color.y, fragmentColor.z, 1); // debug color
}
