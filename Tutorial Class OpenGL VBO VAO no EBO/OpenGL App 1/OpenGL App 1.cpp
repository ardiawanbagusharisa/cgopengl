#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

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

// Move vertex data as global var
float vertices[] = {
    // positions & colors 
     0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left 
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f  // bottom right 
};

void initShaders() {
	// Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Failed to compile vertex shader\n" << infoLog << std::endl;
    }

	// Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Failed to compile fragment shader\n" << infoLog << std::endl;
    }

	// Attach both shaders to a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Failed to link shaders\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void initBuffers() {
    // Generate the VAO and VBO, and bind them 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// Set vertex attribute pointers: position and color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mouseMove(int x, int y) {
	// Variables for the mouse position 
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float normX = (float)x / width;
    float normY = 1.0f - (float)y / height;

	// Variables for dynamic colors based on mouse position
    float r = normX;
    float g = normY;
    float b = 1.0f - normX * normY;

    // Update all 3 vertex colors
    for (int i = 0; i < 3; ++i) {
        int base = 3 + i * 6; // the color offset in array
		vertices[base + 0] = r * ((i + 1) % 3); // For each iteration, this should be: 3, 9, 15
        vertices[base + 1] = g * ((i + 2) % 3);  
		vertices[base + 2] = b * ((i + 3) % 3);  
    }
    /*
    summary of the colors: 
    Vertex i | ((i+1)%3) | ((i+2)%3) | ((i+3)%3) | Resulting color (r, g, b)
           0 |         1 | 2         | 0         | (r, g, 0)
           1 |         2 | 0         | 1         | (2r, 0, b) → then clamped
           2 |         0 | 1         | 2         | (0, g, b)
    since r/g/b are normalized (between 0.0 and 1.0), 
    multiplying by 0, 1, or 2 just scales to the max or min of the channel.
    */

    glutPostRedisplay();
}

void display() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update all vertex colors (3 vertices × 3 floats)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 3 * 3 * sizeof(float), &vertices[3]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glutCreateWindow("Dynamic Triangle Colors");

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    initShaders();
    initBuffers();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}
