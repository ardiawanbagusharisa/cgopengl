#include <GL/glew.h>
#include <GL/freeglut.h>

void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green rectangle
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRectangle(-0.5f, -0.5f, 1.0f, 1.0f); // Draw a rectangle centered in screen

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Rectangle");

    glewInit();
    glClearColor(0, 0, 0, 1); // Black background

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
