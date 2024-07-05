#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
// layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 aNormal;


out vec3 fragmentColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_Perspective;
uniform mat4 u_Translate;
uniform mat4 u_Scale;
uniform mat4 u_Rotate;
uniform mat4 u_View;
void main() {
  mat4 model = u_Translate * u_Rotate * u_Scale;
  gl_Position = u_Perspective * u_View * model * vec4(aPos, 1);

  FragPos = vec3(model * vec4(aPos, 1));
  // fragmentColor = vColor;
  Normal = mat3(transpose(inverse(model))) * aNormal;
}

#shader fragment
#version 330 core

in vec3 fragmentColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 u_Color; 
uniform vec3 u_ViewPos; 
uniform vec3 u_LightPos;
uniform vec3 u_LightColor; 
// uniforms TODO
float ambientStrength = 0.2;

layout(location = 0) out vec4 FragColor;

void main() {
    // light and normal vec 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);

    // ambient ligthing
    vec3 ambient = ambientStrength * u_LightColor;

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    // Specular Lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    // Final color calculation
    vec4 color = vec4(u_Color.x, u_Color.y, u_Color.z, 1.0); 
    vec3 result = (ambient + diffuse + specular) * color.rgb;

    // Output final color
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(1, 1, 1, 1); // debug white
    // FragColor = color; // debug color
}
