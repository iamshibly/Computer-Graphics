#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#define pi 3.142857
using namespace std;

// State variables
int currentLight = 0; // 0 = Red, 1 = Green, 2 = Yellow

void drawCircle(float x, float y, float radius, int r, int g, int b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        float dx = x + radius * cos(angle);
        float dy = y + radius * sin(angle);
        glVertex2f(dx, dy);
    }
    glEnd();
}

void drawTrafficLight() {
    // Draw the pole
    glColor3ub(50, 50, 50);
    glRectf(240, 50, 260, 400);

    // Draw the signal box
    glColor3ub(0, 0, 0);
    glRectf(200, 200, 300, 400);

    // Draw the lights
    drawCircle(250, 350, 30, currentLight == 0 ? 255 : 100, 0, 0);   // Red
    drawCircle(250, 300, 30, 255, 255, currentLight == 2 ? 0 : 100);
    drawCircle(250, 250, 30, 0, currentLight == 1 ? 255 : 100, 0);   // Green
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTrafficLight();
    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1.0, 1.0);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == ' ') { // Spacebar changes the light
        currentLight = (currentLight + 1) % 3; // Cycle through 0, 1, 2
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Traffic Light Signal");
    myInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}
