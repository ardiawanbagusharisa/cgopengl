#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vertexColor;
uniform bool useSolidColor;
void main() {
    gl_Position = vec4(aPos, 1.0);
    if (!useSolidColor)
        vertexColor = aColor;
    else
        // will be overridden in fragment, dummy value 
        vertexColor = vec3(0.0); 
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
uniform bool useSolidColor;
uniform vec3 solidColor;
void main() {
        // use solid color?  
    FragColor = useSolidColor ? vec4(solidColor, 1.0) : vec4(vertexColor, 1.0);
}
)";

GLuint shaderProgram;
GLuint VAO;
GLuint VBO;
GLint useSolidColorLoc;
GLint solidColorLoc;
bool isSolidColor = false;


float vertices[] = {
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // red 
     0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // green 
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // blue
     0.5f, -0.5f, 0.0f,   1.0f, 0.5f, 0.0f  // orange
};


void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader error: " << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader error: " << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader linking error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Get uniform locations
    useSolidColorLoc = glGetUniformLocation(shaderProgram, "useSolidColor");
    solidColorLoc = glGetUniformLocation(shaderProgram, "solidColor");
}

void initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void display() {
    glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform1i(useSolidColorLoc, isSolidColor);
	float r = rand() % 256 / 255.0f; // Random color
    float g = rand() % 256 / 255.0f; // Random color
    float b = rand() % 256 / 255.0f; // Random color
    //std::cout << "Random color: " << r << std::endl;
    glUniform3f(solidColorLoc, r, g, b);  

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glFlush();
}

void keyPress(unsigned char key, int x, int y) {
    if (key == 'C' || key == 'c') {
        isSolidColor = !isSolidColor;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Color Interpolation Toggle (Press 'C')");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW Initialization Failed!" << std::endl;
        return -1;
    }

    initShaders();
    initBuffers();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);

    glutMainLoop();
    return 0;
}
