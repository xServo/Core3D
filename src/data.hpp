#pragma once
// included in GameObject.cpp
// CUBE DATA 
float positions[] = {
  -1.0f, -1.0f, -1.0f, // 0: Bottom-left-back
  1.0f, -1.0f, -1.0f, // 1: Bottom-right-back
  1.0f,  1.0f, -1.0f, // 2: Top-right-back
  -1.0f,  1.0f, -1.0f, // 3: Top-left-back
  -1.0f, -1.0f,  1.0f, // 4: Bottom-left-front
  1.0f, -1.0f,  1.0f, // 5: Bottom-right-front
  1.0f,  1.0f,  1.0f, // 6: Top-right-front
  -1.0f,  1.0f,  1.0f  // 7: Top-left-front
};
/* // color buffer */
/* float colors[] = { */
/*   0.583f,  0.771f,  0.014f, */

/*   0.597f,  0.770f,  0.761f, */
/*   0.597f,  0.770f,  0.761f, */

/*   0.014f,  0.184f,  0.576f, */
/*   0.014f,  0.184f,  0.576f, */

/*   0.997f,  0.513f,  0.064f, */

/*   0.055f,  0.953f,  0.042f, */

/*   0.982f,  0.099f,  0.879f, */
/* }; */
unsigned int indicies[] = {
  // Back face
  0, 1, 2,
  2, 3, 0,

  // Front face
  4, 5, 6,
  6, 7, 4,

  // Left face
  0, 3, 7,
  7, 4, 0,

  // Right face
  1, 5, 6,
  6, 2, 1,

  // Bottom face
  0, 4, 5,
  5, 1, 0,

  // Top face
  3, 2, 6,
  6, 7, 3
};
