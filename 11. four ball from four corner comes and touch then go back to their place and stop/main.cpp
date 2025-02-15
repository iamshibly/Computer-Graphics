#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
using namespace std;

float x1 = 10;
float y11 = 10;
float x2 = 490;
float y2 = 10;
float x3 = 490;
float y3 = 490;
float x4 = 10;
float y4 = 490;

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
    glClearColor(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -10.0, 10.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    circle(x1, y11);
    circle(x2, y2);
    circle(x3, y3);
    circle(x4, y4);

    glFlush();
}

void update(int value) {
    if (animationStopped) {
        return; // Stop animation when it's completed
    }

    // Check if the balls are moving towards the center
    if (movingToCenter) {
        // Move towards the center
        if (x1 < 250) x1 += speed;
        if (y11 < 250) y11 += speed;
        if (x2 > 250) x2 -= speed;
        if (y2 < 250) y2 += speed;
        if (x3 > 250) x3 -= speed;
        if (y3 > 250) y3 -= speed;
        if (x4 < 250) x4 += speed;
        if (y4 > 250) y4 -= speed;

        // Check if all balls have reached the center
        if (x1 >= 250 && y11 >= 250 && x2 <= 250 && y2 >= 250 && x3 <= 250 && y3 <= 250 && x4 >= 250 && y4 <= 250) {
            movingToCenter = false; // Reverse direction
        }
    } else {
        // Move back to the original positions
        if (x1 > 10) x1 -= speed;
        if (y11 > 10) y11 -= speed;
        if (x2 < 490) x2 += speed;
        if (y2 > 10) y2 -= speed;
        if (x3 < 490) x3 += speed;
        if (y3 < 490) y3 += speed;
        if (x4 > 10) x4 -= speed;
        if (y4 < 490) y4 += speed;

        // Check if all balls have returned to their original positions
        if (x1 <= 10 && y11 <= 10 && x2 >= 490 && y2 <= 10 && x3 >= 490 && y3 >= 490 && x4 <= 10 && y4 >= 490) {
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
    glutCreateWindow("Bouncing Balls");
    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
