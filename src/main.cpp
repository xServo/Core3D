#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;

    // Read through the shader file line by line
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            // Change the type based on the shader type declaration in the file
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            // Append the current line to the appropriate stringstream
            if (type != ShaderType::NONE) {
                ss[static_cast<int>(type)] << line << '\n';
            }
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // error handlign
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length; 
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // linking
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void init();
void quit();
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 10.0f;
GLFWwindow* gWindow = NULL;

int main() {
    init();

    float positions[] = {
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f
    };
    unsigned int indicies[] = {
        0, 1, 2,
        0, 2, 6,
        
        3, 0, 6,
        3, 6, 4,
        
        4, 0, 5,
        5, 0, 3,

        1, 7, 2,
        1, 4, 7,

        7, 4, 3,
        7, 3, 6,

        0, 1, 4,
        5, 6, 2,

        5, 6, 3,
        5, 4, 7
    };
    // color buffer
    static const float colors[] = {
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,

        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,

        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,

        0.997f,  0.513f,  0.064f,
        0.997f,  0.513f,  0.064f,
        0.997f,  0.513f,  0.064f,
        0.997f,  0.513f,  0.064f,
        0.997f,  0.513f,  0.064f,
        0.997f,  0.513f,  0.064f,

        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,

        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
    };

    // vao stuff
    unsigned int VAO; 
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);

    // color buffer
    unsigned int cb;
    glGenBuffers(1, &cb); 
    glBindBuffer(GL_ARRAY_BUFFER, cb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); 
    
    // buffer stuff
    VertexBuffer vb(positions, (3*36)*sizeof(float));
    glEnableVertexAttribArray(0);
    // index, values per vertex, type, normalize?, size of vertex in bytes, offset to first vertex 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); // links currently bound array buffer to vao [0]
    IndexBuffer ib(indicies, 42);
    

    // shader stuff
    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    // projection stuff
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
    int u_Perspective = glGetUniformLocation(shader, "u_Perspective");
    glUniformMatrix4fv(u_Perspective, 1, GL_FALSE, &perspective[0][0]);

    // rotate
    glm::mat4 rotate = glm::mat4(1.0f); // initialize identity matrix
    rotate = glm::rotate(rotate, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    int u_Rotate = glGetUniformLocation(shader, "u_Rotate");
    glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &rotate[0][0]);

    // translate
    glm::mat4 translate = glm::mat4(1);
    translate = glm::translate(translate, glm::vec3(0, 0, -2.5));
    int u_Translate = glGetUniformLocation(shader, "u_Translate");
    glUniformMatrix4fv(u_Translate, 1, GL_FALSE, &translate[0][0]);
    
    // scale scaling
    glm::mat4 scale = glm::mat4(1);
    scale = glm::scale(scale, glm::vec3(0.5, 0.5, 0.5)); // scales to 0.5x
    int u_Scale = glGetUniformLocation(shader, "u_Scale");
    glUniformMatrix4fv(u_Scale, 1, GL_FALSE, &scale[0][0]);

    // uniform stuff
    // mat4 rotate;
    // mat4 view;
    // mat4 projection;

    int u_location = glGetUniformLocation(shader, "u_Color");
    float r = 0.0f;
    float incr = 0.002f;
    while (!glfwWindowShouldClose(gWindow)) {
        rotate = glm::rotate(rotate, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(u_Rotate, 1, GL_FALSE, &rotate[0][0]);
        r += incr;
        if (r > 0.5f) {
            r = 0.5f;
            incr = -0.002f;
        } else if (r < 0) {
            r = 0;
            incr = 0.002f;
        }
        glUniform4f(u_location, r, 0.3, -r, 1);
        // Render here (currently just a clear color)
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe mode:w

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw call
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // use ib
        glDrawArrays(GL_TRIANGLES, 0, 36*3); // use vertex matrix
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        // error check
        ASSERT(GLLogCall());
        
        // Swap buffers to display the updated frame
        glfwSwapBuffers(gWindow);
        // Poll for and process events
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);
    quit();
    // printf("hello world\n");
}

void init() {
    if (!glfwInit()) {
        printf("Error! Failed to initialize gflw");
    } else {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "graphics ryan graphcis", NULL, NULL);
        glViewport(0, 0, 800, 600);
        if (!gWindow)
        {
            printf("Error! Failed to create OpenGL context or window");
            return;
        } else {
            glfwMakeContextCurrent(gWindow);

            glfwSwapInterval(1); // enable vsync

            printf("GLEW Version %s\n", glewGetString(GLEW_VERSION));
            printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
                return;
            }
        }
    }
}
void quit() {
    printf("Quitting...\n");
    glfwDestroyWindow(gWindow);
    glfwTerminate();
}