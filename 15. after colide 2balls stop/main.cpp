#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define pi 3.142857

using namespace std;

float x_left = 0, y_left = 250;   // Left ball starts at (0,250)
float x_right = 500, y_right = 250; // Right ball starts at (500,250)

float speed = 2.0;
bool movingToCenter = true;  // Controls movement direction

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

    circle(x_left, y_left);
    circle(x_right, y_right);

    glFlush();
}

void update(int value) {
    if (movingToCenter) {
        // Move both balls towards the center
        if (x_left < 250) x_left += speed;
        if (x_right > 250) x_right -= speed;

        // Stop moving when both balls meet at the center
        if (x_left >= 250 && x_right <= 250) {
            movingToCenter = false; // Stop further updates
            return; // Exit the function to stop movement
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
    glutCreateWindow("Left-Right Collision Stop");
    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
