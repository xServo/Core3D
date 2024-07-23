#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 u_Perspective;
uniform mat4 u_Translate;
uniform mat4 u_Scale;
uniform mat4 u_Rotate;
uniform mat4 u_View;

void main() {
  mat4 model = u_Translate * u_Rotate * u_Scale;
  gl_Position = u_Perspective * u_View * model * vec4(aPos, 1);

  FragPos = vec3(model * vec4(aPos, 1));
  Normal = mat3(transpose(inverse(model))) * aNormal;
  TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}

#shader fragment
#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform int u_IsLit;
uniform int u_IsTextured;
uniform vec3 u_Color; 
uniform vec3 u_ViewPos; 
uniform sampler2D u_Texture;

struct Material {
  float shininess;
};
uniform Material material;

struct PointLight {
  vec3 lightPos;
  vec3 lightColor;
};
const int LIGHT_COUNT = 2;
uniform PointLight lights[LIGHT_COUNT];

float ambientStrength = 0.3;
float specularStrength = 0.5;
layout(location = 0) out vec4 FragColor;

void main() {
  vec4 color;
  if (u_IsTextured == 1) {
    color = texture(u_Texture, TexCoords);
  } else {
    color = vec4(u_Color.x, u_Color.y, u_Color.z, 1.0); 
  }
  
  if (u_IsLit == 1) {
    vec3 ambient = ambientStrength * vec3(0.2, 0.2, 0.2);
    vec3 norm = normalize(Normal);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < LIGHT_COUNT; i++) {
      vec3 lightDir = normalize(lights[i].lightPos - FragPos);
      
      // Diffuse lighting
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * lights[i].lightColor;
      totalDiffuse += diffuse;
      
      // Specular lighting
      vec3 viewDir = normalize(u_ViewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular = specularStrength * spec * lights[i].lightColor;
      totalSpecular += specular;
    }

    vec3 result = (ambient + totalDiffuse + totalSpecular) * color.rgb;

    FragColor = vec4(result, 1.0);
  } else {
    FragColor = vec4(u_Color.x, u_Color.y, u_Color.z, 1.0);
  }
}
