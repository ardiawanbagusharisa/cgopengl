#include <GL/glew.h>
#include <GL/freeglut.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
	glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
	glBegin(GL_QUADS); // Start drawing a square
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glFlush(); // Render now
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL Setup Test");
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}