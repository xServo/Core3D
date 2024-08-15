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
vec4 Standard();
vec4 BlackWhite();
vec4 BoxBlur(int degree);

vec4 color;
void main() {
    color = BoxBlur(10);

    FragColor = BlackWhite();
}

vec4 Standard() {
    return texture(u_Texture, TexCoords);
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

vec4 BoxBlur(int degree) {
    vec4 tempColor = vec4(0, 0, 0, 1);
    for (int i = -degree / 2; i < degree - degree / 2; i++) {
        for (int j = -degree / 2; j < degree - degree / 2; j++) {
            // get neighbor coords
            vec2 neighborCoords = TexCoords + vec2(i, j) / textureSize(u_Texture, 0); // normalize
            // get neighbor color
            vec4 neighborColor = texture(u_Texture, neighborCoords);
            tempColor += neighborColor;
        }
    }
    // average out
    tempColor /= float(degree * degree);
    return tempColor;
}