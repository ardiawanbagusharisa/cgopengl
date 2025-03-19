#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>

struct Point {
	float x, y;
};	

std::vector<Point> controlPoints;
int selectedPoint = -1;

void drawPoint(float x, float y) {
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawBezierCurve() {
	if (controlPoints.size() < 2) return;

	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP); 
	for (float t = 0; t <= 1; t += 0.05f) {
		float x = 0;
		float y = 0;

		int n = controlPoints.size() - 1;
		for (int i = 0; i <= n; i++) {
			float binomial = tgamma(n + 1) / (tgamma(i + 1) * tgamma(n - i + 1));		// This is the binomial coefficient
			float blend = binomial * pow(t, i) * pow(1 - t, n - i);						// This is the blending function
			x += controlPoints[i].x * blend;
			y += controlPoints[i].y * blend;
		}
		glVertex2f(x, y);
	}
	glEnd();
}

void drawControlPoints() {
	for (int i = 0; i < controlPoints.size(); i++) {
		if (i == selectedPoint) {
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		drawPoint(controlPoints[i].x, controlPoints[i].y);
	}
}

void mouse(int button, int state, int x, int y) {
	float mx = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1;
	float my = -(float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2) + 1;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		controlPoints.push_back({ mx, my });
		selectedPoint = controlPoints.size() - 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < controlPoints.size(); i++) {
			float dx = controlPoints[i].x - mx; 
			float dy = controlPoints[i].y - my;
			if (fabs(dx) < 0.05f && fabs(dy) < 0.05f) {  // This is not pixel unit. This is in the normalized range of -1 to 1. 
				// Debug the dx and dy 
				printf("dx: %f, dy: %f\n", dx, dy);
				selectedPoint = i;
				break;
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		selectedPoint = -1;
	}

	glutPostRedisplay();
}

void motion(int x, int y) {
	if (selectedPoint != -1) {
		controlPoints[selectedPoint].x = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1; // dont hardcode the window size. use glutGet(GLUT_WINDOW_WIDTH) and glutGet(GLUT_WINDOW_HEIGHT)
		controlPoints[selectedPoint].y = -(float)y / (glutGet(GLUT_WINDOW_WIDTH) / 2) + 1;
		glutPostRedisplay();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);		// Clear the screen
	glColor3f(1.0f, 0.0f, 0.0f);		// Set color to red

	drawBezierCurve();
	drawControlPoints();

	glFlush();							// Render now
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Set background color to black and opaque
	glMatrixMode(GL_PROJECTION);			// To operate on the Projection matrix
	glLoadIdentity();						// Reset the projection matrix
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);		// Set the viewport
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Simple Train Simulation");
	glewInit();

	initGL();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}