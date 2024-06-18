opengl pipeline
- supply the graphics card with data
- on vram
- use shader that reads the data and draws

vertex buffer is read by shader

a vertex can contain more than just position
these are called attributes:
- position
- texture coord
- normals
- colors
- binormals
- tangents
the stride is the amt of bytes between each vertex

a shader runs on the gpu
2 main types: 
- vertex 
  - specifies position of vertex)
  - passes attributes to next stage
- fragment/pixel
  - decides color foreach pixel
  - gets called A LOT
to actually render (simplified): 
draw call => vertex shader(called for each vertex)=> fragment shader(runs for each pixel) => pixels on screen

Uniforms get data from cpu to gpu
- attributes do this as well
  - uniforms are set per draw
  - attributes are set per vertex

