#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

// Vertex Shader Source
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec3 aPos;
//
//void main() {
//    gl_Position = vec4(aPos, 1.0);
//}
//)";
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";


// Fragment Shader Source
//const char* fragmentShaderSource = R"(
//#version 330 core
//out vec4 FragColor;
//
//void main() {
//    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
//}
//)";
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor, 1.0);
}
)";


GLuint shaderProgram;
GLuint VAO;
GLuint VBO;

void initShaders() {
    // Compile Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex Shader Compilation Failed\n" << infoLog << std::endl;
    }

    // Compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment Shader Compilation Failed\n" << infoLog << std::endl;
    }

    // Link Shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void initBuffers() {
    //float vertices[] = {
    //     0.0f,  0.5f, 0.0f,  // Top
    //    -0.5f, -0.5f, 0.0f,  // Bottom Left
    //     0.5f, -0.5f, 0.0f   // Bottom Right
    //};
    // Now add RGB color to each vertex (x, y, z, r, g, b)
    float vertices[] = {
        // positions         // colors
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // Top - Blue
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom Left - Green 
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f  // Bottom Right - Red
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Binding of VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //// Set vertex attribute pointers
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void display() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // Background
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader and draw
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Pipeline - VBO and VAO");

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    
    initShaders();
    initBuffers();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
