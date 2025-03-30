#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>
#include "OpenGL App 1.h"

const float PI = 3.14159265359f;
struct Color {
	float r, g, b;
};

int window1, window2;
int light = 0;

void drawRect(float cx, float cy, float sizeX, float sizeY, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);				// Start drawing a square

	glVertex2f(cx - sizeX / 2, cy - sizeY / 2);		// Change the method to be more parametric
	glVertex2f(cx + sizeX / 2, cy - sizeY / 2);
	glVertex2f(cx + sizeX / 2, cy + sizeY / 2);
	glVertex2f(cx - sizeX / 2, cy + sizeY / 2);
	
	glEnd();
}

void drawCircle(float cx, float cy, float r, int segments, Color color) {
	glColor3f(color.r, color.g, color.b);		
	glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * PI * float(i) / float(segments);	// Compute the radian angle
		float x = r * cosf(theta);		// Set coordinates of points on the perimeter of the circle using polar to cartesian 
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}

int createWindow(const char* title, int width, int height, int posX, int posY, void (*displayFunc)()) {
	glutInitWindowSize(width, height);
	glutInitWindowPosition(posX, posY);
	int windowID = glutCreateWindow(title);
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// Black background
	glutDisplayFunc(displayFunc);				// Register the display function
	return windowID;
}

void displayTraffic() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawRect(0.0f, -0.75f, 0.1f, 0.5f, { 0.3f, 0.3f, 0.3f });	// Pole
	drawRect(0.0f, 0.0f, 0.5f, 1.2f, { 0.5f, 0.5f, 0.5f });		// Panel	
	drawCircle(0.0f, 0.575f, 0.25f, 100, { 0.5f, 0.5f, 0.5f });	// Facades 
	drawCircle(0.0f, 0.45f, 0.15f, 100, { 0.3f, 0.3f, 0.3f });	
	drawCircle(0.0f, 0.05f, 0.15f, 100, { 0.3f, 0.3f, 0.3f });	
	drawCircle(0.0f, -0.35f, 0.15f, 100, { 0.3f, 0.3f, 0.3f });	

	if (light == 1) {
		drawCircle(0.0f, 0.4f, 0.15f, 100, { 1.0f, 0.0f, 0.0f });	// Red
	}
	else if (light == 2) {
		drawCircle(0.0f, 0.0f, 0.15f, 100, { 1.0f, 1.0f, 0.0f });	// Yellow 
	}
	else if (light == 3) {
		drawCircle(0.0f, -0.4f, 0.15f, 100, { 0.0f, 1.0f, 0.0f });	// Green 
	}

	glFlush();
}

void updateTraffic(int value) {
	//glutSetWindow(window1);
	// make the traffic light change colors every 3 seconds
	light = light < 3 ? ++light : 1;
	printf("Light: %d\n", light);
	glutPostRedisplay();
	glutTimerFunc(2000, updateTraffic, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	window1 = createWindow("Traffic Light", 400, 400, 50, 50, displayTraffic);
	updateTraffic(0);

	glutMainLoop();
	return 0;
}

