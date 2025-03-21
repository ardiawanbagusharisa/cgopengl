#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>

struct Point {
	float x, y;
};	

std::vector<Point> controlPoints;
int selectedPoint = -1;
bool isTrainMoving = true;
float trainMovePos = 0.0f;

Point getBezierPoints(float t) {
	int n = controlPoints.size() - 1;
	Point p = { 0, 0 };

	for (int i = 0; i <= n; i++) {
		float binomial = tgamma(n + 1) / (tgamma(i + 1) * tgamma(n - i + 1));		// This is the binomial coefficient
		float blend = binomial * pow(t, i) * pow(1 - t, n - i);						// This is the blending function
		p.x += controlPoints[i].x * blend;
		p.y += controlPoints[i].y * blend;
	}
	return p;
}

Point getTangentPoints(float t) {
	int n = controlPoints.size() - 1;
	if (n < 1) {
		return { 0, 0 };
	}
	
	Point tangent = { 0, 0 };
	for (int i = 0; i < n; i++) {
		float binomial = tgamma(n) / (tgamma(i + 1) * tgamma(n - i)); 
		float blend = binomial * pow(t, i) * pow(1 - t, n - 1 - i);	
		tangent.x += (controlPoints[i + 1].x - controlPoints[i].x) * blend * n;
		tangent.y += (controlPoints[i + 1].y - controlPoints[i].y) * blend * n;
	}

	return tangent;
}

void drawPoint(float x, float y) {
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawBezierCurve() {
	if (controlPoints.size() < 2) {
		return;
	}

	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP); 
	for (float t = 0; t <= 1; t += 0.05f) {
		Point p = getBezierPoints(t);
		glVertex2f(p.x, p.y);
	}
	glEnd();
}

void drawRails() {
	if (controlPoints.size() < 2) {
		return;
	}

	glColor3f(0.8f, 0.6f, 0.5f);		// Wooden color for sleepers
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	for (float t = 0; t <= 1; t += 0.05f) {
		Point p = getBezierPoints(t);
		Point tangent = getTangentPoints(t); 

		// Get the perpendicular vector by normalizing the tangent vector and then rotating it by 90 degrees
		float length = sqrt(pow(tangent.x, 2) + pow(tangent.y, 2));
		if (length == 0) {
			continue;
		}
		tangent.x = tangent.x / length;
		tangent.y = tangent.y / length;
		Point normal = { -tangent.y, tangent.x };

		glVertex2f(p.x - normal.x * 0.02f, p.y - normal.y * 0.02f);
		glVertex2f(p.x + normal.x * 0.02f, p.y + normal.y * 0.02f);
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

void drawTrain() {
	if (controlPoints.size() < 2) {
		return;
	}

	Point trainPos = getBezierPoints(trainMovePos);
	Point trainTangent = getTangentPoints(trainMovePos);

	float length = sqrt(pow(trainTangent.x, 2) + pow(trainTangent.y, 2));
	if (length == 0) {
		return;
	}
	trainTangent.x = trainTangent.x / length;
	trainTangent.y = trainTangent.y / length;
	Point normal = { -trainTangent.y, trainTangent.x };

	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(trainPos.x - normal.x * 0.05f - trainTangent.x * 0.04f, trainPos.y - normal.y * 0.05f - trainTangent.y * 0.04f);
	glVertex2f(trainPos.x + normal.x * 0.05f - trainTangent.x * 0.04f, trainPos.y + normal.y * 0.05f - trainTangent.y * 0.04f);
	glVertex2f(trainPos.x + normal.x * 0.05f + trainTangent.x * 0.04f, trainPos.y + normal.y * 0.05f + trainTangent.y * 0.04f);
	glVertex2f(trainPos.x - normal.x * 0.05f + trainTangent.x * 0.04f, trainPos.y - normal.y * 0.05f + trainTangent.y * 0.04f);
	glEnd();

	// Update the train position
}

void updateTrain(int value) {
	if (isTrainMoving) {
		trainMovePos += 0.005f;
		if (trainMovePos > 1.0f) trainMovePos = 0.0f;
		glutPostRedisplay();
		glutTimerFunc(100, updateTrain, value);
	}
}

void mouse(int button, int state, int x, int y) {
	// Change the coordinate system from pixel to normalized range of -1 to 1
	// Don't hardcode the window size. Use window width and height. 
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
		// Change the coordinate system from pixel to normalized range of -1 to 1
		// Don't hardcode the window size. Use window width and height. 
		controlPoints[selectedPoint].x = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1; 
		controlPoints[selectedPoint].y = -(float)y / (glutGet(GLUT_WINDOW_WIDTH) / 2) + 1;
		glutPostRedisplay();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the screen
	glColor3f(1.0f, 0.0f, 0.0f);	// Set color to red

	drawBezierCurve();
	drawRails();
	drawControlPoints();
	drawTrain();

	glFlush();						// Render now
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
	glutInitWindowSize(600, 600);
	glutCreateWindow("Simple Train Simulation");
	glewInit();

	initGL();
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	updateTrain(0);

	glutMainLoop();
	return 0;
}

// [Todo] 
/*
1. Train: add more carriages, smoke, light, sound, speed control. 
2. Track: track type, station. 
3. Environment: fractal tree, cloud, rain, rain ripples. 
4. UI: buttons (speed, weather). 
*/