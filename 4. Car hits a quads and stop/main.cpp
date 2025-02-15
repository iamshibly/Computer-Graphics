#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

float carX = 10, carY = 200;
bool movingRight = true;
float quadX = 250, quadY = 480;
bool quadFalling = true;
bool collisionDetected = false;
float carSpeed = 2.0f;
float quadSpeed = 3.0f;

void circle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(222, 219, 214);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        float a = x + radius * cos(i * (3.1416 / 180));
        float b = y + radius * sin(i * (3.1416 / 180));
        glVertex2f(a, b);
    }
    glEnd();
}

void car(float x, float y) {
    glBegin(GL_QUADS);
    glColor3ub(207, 124, 0);
    glVertex2f(x, y);
    glVertex2f(x + 50, y);
    glVertex2f(x + 50, y + 10);
    glVertex2f(x, y + 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(50, 124, 20);
    glVertex2f(x + 5, y + 10);
    glVertex2f(x + 45, y + 10);
    glVertex2f(x + 40, y + 20);
    glVertex2f(x + 10, y + 20);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(100, 50, 200);
    glVertex2f(x + 10, y + 20);
    glVertex2f(x + 40, y + 20);
    glVertex2f(x + 25, y + 30);
    glEnd();

    circle(x + 10, y, 6);
    circle(x + 40, y, 6);
}

void quad() {
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 0);
    glVertex2f(quadX, quadY);
    glVertex2f(quadX + 20, quadY);
    glVertex2f(quadX + 20, quadY - 20);
    glVertex2f(quadX, quadY - 20);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    car(carX, carY);
    quad();
    glFlush();
}

void update(int value) {
    if (!collisionDetected) {
        if (movingRight) {
            carX += carSpeed;
            if (carX + 50 > WINDOW_WIDTH) movingRight = false;
        } else {
            carX -= carSpeed;
            if (carX < 0) movingRight = true;
        }

        if (quadFalling) {
            quadY -= quadSpeed;
            if (quadY - 20 <= carY + 10 && quadY >= carY && quadX + 20 >= carX && quadX <= carX + 50) {
                collisionDetected = true;
                quadFalling = false; // Stop the quad when collision happens
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (carSpeed > 1.0f) carSpeed -= 1.0f;
            break;
        case GLUT_KEY_RIGHT:
            carSpeed += 1.0f;
            break;
        case GLUT_KEY_UP:
            quadSpeed += 1.0f;
            break;
        case GLUT_KEY_DOWN:
            if (quadSpeed > 1.0f) quadSpeed -= 1.0f;
            break;
    }
}

void myInit() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -10.0, 10.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Car and Falling Quad Collision");
    myInit();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
