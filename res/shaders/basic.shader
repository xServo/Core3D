#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 u_Perspective;
uniform mat4 u_View;

uniform mat4 u_Model;

void main() {
  gl_Position = u_Perspective * u_View * u_Model * vec4(aPos, 1);

  FragPos = vec3(u_Model * vec4(aPos, 1));
  Normal = mat3(transpose(inverse(u_Model))) * aNormal;
  TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}

#shader fragment
#version 330 core
const float PI = 3.14159265359;


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
  float ao;
  float metallic;
  float roughness;
};
uniform Material material;

struct PointLight {
  vec3 lightPos;
  vec3 lightColor;
};
const int LIGHT_COUNT = 3;
uniform PointLight lights[LIGHT_COUNT];

float ambientStrength = 0.3;
float specularStrength = 0.5;
layout(location = 0) out vec4 FragColor;

vec3 CalculatePhong(vec4 color);
vec3 CalculatePBR(vec4 color);

void main() {
  vec4 color;
  if (u_IsTextured == 1) {
    color = texture(u_Texture, TexCoords);
  } else {
    color = vec4(u_Color.x, u_Color.y, u_Color.z, 1.0);
  }

  if (u_IsLit == 1) {
//    FragColor = vec4(CalculatePhong(color), 1.0);
    FragColor = vec4(CalculatePBR(color), 1.0);
  } else {
    FragColor = vec4(u_Color.x, u_Color.y, u_Color.z, 1.0);
  }
}

vec3 CalculatePhong(vec4 color) {
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
  return vec3((ambient + totalDiffuse + totalSpecular) * color.rgb);
}
// TODO GRAPHICS RESEARCH
float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float a = roughness * roughness;
  float a2 = a * a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float numerator = a2;
  float denominator = (NdotH2 * (a2 - 1.0) + 1.0);
  denominator = PI * denominator * denominator;

  return numerator / denominator;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float GeometrySchlickGGX(float NdotV, float roughness) {
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;

  float numerator = NdotV;
  float denominator = NdotV * (1.0 - k) + k;

  return numerator / denominator;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
  float NdotV = max(dot(N, V), 0.0);
  float NdotL = max(dot(N, L), 0.0);
  float ggx2 = GeometrySchlickGGX(NdotV, roughness);
  float ggx1 = GeometrySchlickGGX(NdotL, roughness);

  return ggx1 * ggx2;
}


vec3 CalculatePBR(vec4 color) {
  vec3 albedo = color.rgb;
  float metallic = material.metallic;
  float roughness = material.roughness;
  float ao = material.ao; // Ambient Occlusion
//  float metallic = 0;
//  float roughness = 0.2;
//  float ao = 0.5;// Ambient Occlusion

  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(u_ViewPos - FragPos);

  vec3 F0 = vec3(0.04);// base reflectivity at normal incidence
  F0 = mix(F0, albedo, metallic);

  vec3 Lo = vec3(0.0);// Output light color

  for (int i = 0; i < LIGHT_COUNT; i++) {
    vec3 lightDir = normalize(lights[i].lightPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Distance to the light
    float distance = length(lights[i].lightPos - FragPos);
    float spreadFactor = 1; // Makes the light spread more
    float attenuation = 1.0 / (distance * distance * spreadFactor);
    float intensityFactor = 0.8; // Lowering this value spreads the light more
    vec3 radiance = lights[i].lightColor * attenuation * intensityFactor;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(norm, halfwayDir, roughness);
    float G = GeometrySmith(norm, viewDir, lightDir, roughness);
    vec3 F = FresnelSchlick(max(dot(halfwayDir, viewDir), 0.0), F0);

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(norm, viewDir), 0.0) * max(dot(norm, lightDir), 0.0) + 0.001;// Prevent divide by zero
    vec3 specular = numerator / denominator;

    // kS is the specular component, and kD is the diffuse component
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;// Only non-metallic surfaces have diffuse component

    // Lambertian diffuse
    float NdotL = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = kD * albedo / PI;

    // Combine results
    Lo += (diffuse + specular) * radiance * NdotL;
  }

  // Ambient lighting (approximate IBL)
  vec3 ambient = ambientStrength * albedo * ao;

  vec3 colorOutput = ambient + Lo;
  return colorOutput;
}
