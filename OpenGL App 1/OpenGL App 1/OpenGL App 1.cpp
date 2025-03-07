#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

const float PI = 3.14159265359f;
struct Color {
	float r, g, b;
};

void drawRect(float cx, float cy, float sizeX, float sizeY) {
	glColor3f(1.0f, 0.0f, 0.0f);	// Set color to red
	glBegin(GL_QUADS);				// Start drawing a square

	glVertex2f(cx - sizeX / 2, cy - sizeY / 2);		// Change the method to be more parametric
	glVertex2f(cx + sizeX / 2, cy - sizeY / 2);
	glVertex2f(cx + sizeX / 2, cy + sizeY / 2);
	glVertex2f(cx - sizeX / 2, cy + sizeY / 2);
	
	glEnd();
}

void drawCircle(float cx, float cy, float r, int segments, Color color) {
	glColor3f(color.r, color.g, color.b);		// Set color to white
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * PI * float(i) / float(segments);	// Compute the radian angle
		float x = r * cosf(theta);				// Set coordinates of points on the perimeter of the circle using polar to cartesian 
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the screen

	// Draw something 
	//drawRect(0.0f, 0.0f, 1.0f, 1.0f);
	drawCircle(0.0f, 0.0f, 0.5f, 100, { 1.0f, 1.0f, 0.7f });	// First circle, a little bit yellow
	drawCircle(0.2f, 0.1f, 0.5f, 100, { 0.0f, 0.0f, 0.0f });	// Slightly moved black circle
	glFlush();								// Render now
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL Setup Test");
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// Black background
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

