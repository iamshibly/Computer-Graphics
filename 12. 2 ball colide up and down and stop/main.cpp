#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define pi 3.142857

using namespace std;

float x_top = 250, y_top = 500;  // Top ball
float x_bottom = 250, y_bottom = 0;  // Bottom ball

float speed = 2.0;
bool movingToCenter = true;
bool animationStopped = false;

void circle(float x, float y) {
    float radius = 10;
    double pii = 3.1416;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(22, 219, 14);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        glColor3ub(44, 66, 174);
        float a = x + radius * cos(i * (pii / 180));
        float b = y + radius * sin(i * (pii / 180));
        glVertex2f(a, b);
    }
    glEnd();
}

void myInit() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -10.0, 10.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    circle(x_top, y_top);
    circle(x_bottom, y_bottom);

    glFlush();
}

void update(int value) {
    if (animationStopped) {
        return; // Stop animation when completed
    }

    if (movingToCenter) {
        // Move both balls towards the center
        if (y_top > 250) y_top -= speed;
        if (y_bottom < 250) y_bottom += speed;

        // Check if both balls reached the center
        if (y_top <= 250 && y_bottom >= 250) {
            movingToCenter = false; // Reverse direction
        }
    } else {
        // Move both balls back to their original positions
        if (y_top < 500) y_top += speed;
        if (y_bottom > 0) y_bottom -= speed;

        // Check if both balls returned to their original positions
        if (y_top >= 500 && y_bottom <= 0) {
            animationStopped = true; // Stop animation
        }
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Two Balls Collision");
    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
