#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

const float PI = 3.14159265359f;
struct Color {
	float r, g, b;
};

int window1, window2;

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

void displayMoon() {
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the screen

	drawCircle(0.0f, 0.0f, 0.5f, 100, { 1.0f, 1.0f, 0.7f });	// First circle, a little bit yellow
	drawCircle(0.2f, 0.1f, 0.5f, 100, { 0.0f, 0.0f, 0.0f });	// Slightly moved black circle

	glFlush();								// Render now
}

void displaySmiley() {
	glClear(GL_COLOR_BUFFER_BIT);			// Clear the screen
	drawCircle(0.0f, 0.0f, 0.6f, 100, { 1.0f, 0.8f, 0.6f });		// Main face
	drawCircle(-0.275f, 0.275f, 0.2f, 100, { 1.0f, 1.0f, 1.0f });	// Left eye
	drawCircle(-0.25f, 0.25f, 0.1f, 100, { 0.0f, 0.0f, 0.0f });
	drawCircle(0.275f, 0.275f, 0.2f, 100, { 1.0f, 1.0f, 1.0f });	// Right eye
	drawCircle(0.25f, 0.25f, 0.1f, 100, { 0.0f, 0.0f, 0.0f });
	drawCircle(0.0f, -0.25f, 0.2f, 100, { 1.0f, 0.0f, 0.0f });		// Mouth 
	drawRect(0.0f, -0.15f, 0.4f, 0.2f, { 1.0f, 0.8f, 0.6f });	
	drawCircle(-0.35f, 0.0f, 0.175f, 100, { 1.0f, 0.7f, 0.5f });	// Cheeks
	drawCircle(0.35f, 0.0f, 0.175f, 100, { 1.0f, 0.7f, 0.5f });
	drawCircle(0.0f, 0.0f, 0.2f, 100, { 1.0f, 0.6f, 0.4f });		// Nose 
	drawCircle(-0.1f, 0.1f, 0.05f, 100, { 1.0f, 1.0f, 1.0f });		// Highlight
	glFlush();													
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	window1 = createWindow("Crescent Moon", 400, 400, 50, 50, displayMoon);
	window1 = createWindow("Smiley Face", 400, 400, 450, 50, displaySmiley);
	glutMainLoop();
	return 0;
}

