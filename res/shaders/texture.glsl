#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Texture;

/* POST PROCESSING EFFECTS */
vec4 BlackWhite();
vec4 Standard();

vec4 color;
void main() {
    color = texture(u_Texture, TexCoords);

    vec3 brightColor = max(vec3(0.0), color - vec3(0.5, 0.5, 0.5));

    color = Standard();
    FragColor = color;
}

vec4 BlackWhite() {
    float strongestColor;
    if (color.x > color.y && color.x > color.z) {
        strongestColor = color.x;
    } else if (color.z > color.y) {
        strongestColor = color.z;
    } else {
        strongestColor = color.y;
    }
    return vec4(strongestColor, strongestColor, strongestColor, 1);
}



vec4 Standard() {
    return color = vec4(color.x, color.y, color.z, 1);
}