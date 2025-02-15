#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <cmath>

#define pi 3.142857

using namespace std;

float x11 = 250;  // Ball's X position (constant)
float y11 = 20;   // Ball starts from the ground
float velocity = 5.0;  // Initial upward velocity
float gravity = -0.1;  // Gravity effect
float bounceIncrease = 1.1;  // Factor to increase bounce height
bool stopBouncing = false;  // Flag to stop motion

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
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -10.0, 10.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    circle(x11, y11);
    glFlush();
}

void update(int value) {
    if (!stopBouncing) {
        velocity += gravity;  // Apply gravity
        y11 += velocity;  // Update position

        // Check for ground collision
        if (y11 <= 10) {  // Ball hits the ground
            y11 = 10;  // Reset position to ground level
            velocity = -velocity * bounceIncrease;  // Increase bounce height
        }

        // Stop bouncing if it reaches or exceeds y = 500
        if (y11 >= 500) {
            y11 = 500;  // Fix position at max height
            velocity = 0;  // Stop movement
            stopBouncing = true;  // Set flag to stop updates
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
    glutCreateWindow("Increasing Bounce Height with Stop");
    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
