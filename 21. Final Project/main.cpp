#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time
#include <cmath>   // For math functions

#define pi 3.142857

using namespace std;

// Game Variables
bool gameOver = false;
int score = 0;

// Snake and Apple Variables
struct Segment { float x, y; };
vector<Segment> snake = {{250, 300}, {230, 300}, {210, 300}};
float segmentWidth = 20, segmentHeight = 20;
int dirX = 1, dirY = 0, lastDirX = 1, lastDirY = 0;
float snakeSpeed = 1.0f;//0.5f;/
float appleX = 300, appleY = 400;

// Cloud Variables
float cloud1X = 100, cloud2X = 300, cloudY = 600, cloudSpeed = 5.0f;

// Utility Functions
void drawCircle(float x, float y, float radius, int r, int g, int b)
{
    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * pi / 180.0f;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Drawing Functions
void sky()
{
    glBegin(GL_QUADS);
    glColor3ub(135, 206, 235);
    glVertex2f(0, 450); glVertex2f(700, 450); glVertex2f(700, 700); glVertex2f(0, 700);
    glEnd();
    drawCircle(550, 600, 40, 253, 232, 166); // Sun
}

void drawCloud(float x, float y)
{
    drawCircle(x, y, 20, 255, 255, 255);
    drawCircle(x + 30, y, 20, 255, 255, 255);
    drawCircle(x + 15, y + 20, 20, 255, 255, 255);
}

void drawApple()
{
    drawCircle(appleX, appleY, 10, 255, 0, 0);
}

void drawSnake()
{
    for (size_t i = 0; i < snake.size(); ++i)
    {
        int color[3] = {0, 128, 0};
        if (i == 0) color[0] = 34, color[1] = 139, color[2] = 34;
        else if (i % 2 != 0) color[1] = 100;

        glBegin(GL_QUADS);
        glColor3ub(color[0], color[1], color[2]);
        float x = snake[i].x, y = snake[i].y;
        glVertex2f(x - segmentWidth / 2, y - segmentHeight / 2);
        glVertex2f(x + segmentWidth / 2, y - segmentHeight / 2);
        glVertex2f(x + segmentWidth / 2, y + segmentHeight / 2);
        glVertex2f(x - segmentWidth / 2, y + segmentHeight / 2);
        glEnd();

        // Draw eyes for the head
        if (i == 0)
        {
            float eyeOffsetX = segmentWidth / 4.0f, eyeOffsetY = segmentHeight / 4.0f;
            drawCircle(x - eyeOffsetX, y + eyeOffsetY, 4, 255, 255, 255); // Left eye
            drawCircle(x + eyeOffsetX, y + eyeOffsetY, 4, 255, 255, 255); // Right eye
            drawCircle(x - eyeOffsetX, y + eyeOffsetY, 2, 0, 0, 0); // Left pupil
            drawCircle(x + eyeOffsetX, y + eyeOffsetY, 2, 0, 0, 0); // Right pupil
        }
    }
}

// Game Logic
bool checkCollision(float x1, float y1, float x2, float y2, float width, float height)
{
    return x1 < x2 + width && x1 + width > x2 && y1 < y2 + height && y1 + height > y2;
}

void generateApple()
{
    int gridSize = segmentWidth;
    appleX = (rand() % (700 / gridSize)) * gridSize + gridSize / 2;
    appleY = (rand() % (450 / gridSize)) * gridSize + gridSize / 2;
}

void updateClouds()
{
    cloud1X += cloudSpeed;
    cloud2X += cloudSpeed;
    if (cloud1X > 700) cloud1X = -100;
    if (cloud2X > 700) cloud2X = -200;
}

void resetGame()
{
    gameOver = false;
    snake = {{250, 300}, {230, 300}, {210, 300}};
    dirX = 1; dirY = 0;
    generateApple();
}

void updateSnake()
{
    // Store previous positions
    vector<Segment> prevPositions = snake;

    // Calculate next head position
    float nextX = snake[0].x + dirX * segmentWidth;
    float nextY = snake[0].y + dirY * segmentHeight;

    // Check boundaries
    if (nextX < 0 || nextX >= 700 || nextY < 0 || nextY >= 450)
    {
        gameOver = true;
        return;
    }

    // Update head position
    snake[0].x = nextX;
    snake[0].y = nextY;

    // Update body segments - each segment takes previous segment's position
    for (size_t i = 1; i < snake.size(); i++) {
        snake[i] = prevPositions[i-1];
    }

    // Check apple collision
    if (checkCollision(snake[0].x - segmentWidth/2, snake[0].y - segmentHeight/2,
                      appleX - segmentWidth/2, appleY - segmentHeight/2,
                      segmentWidth, segmentHeight))
    {
        snake.push_back(prevPositions.back());
        snake.push_back(prevPositions.back());
        generateApple();
        score++;
    }

    lastDirX = dirX;
    lastDirY = dirY;
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    drawCloud(cloud1X, cloudY);
    drawCloud(cloud2X, cloudY - 50);
    drawSnake();
    drawApple();

    // Display Score
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    glColor3ub(0, 0, 0);
    glRasterPos2f(10, 670);
    for (int i = 0; scoreText[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreText[i]);

    // Game Over Text
    if (gameOver)
    {
        glColor3ub(255, 0, 0);
        glRasterPos2f(300, 350);
        const char *gameOverText = "GAME OVER";
        for (int i = 0; gameOverText[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOverText[i]);
    }

    glFlush();
}

void my_special_keyboard(int key, int x, int y)
{
    if (gameOver && key == 'r') resetGame();
    if (!gameOver)
    {
        if (key == GLUT_KEY_UP && lastDirY == 0) dirX = 0, dirY = 1;
        else if (key == GLUT_KEY_DOWN && lastDirY == 0) dirX = 0, dirY = -1;
        else if (key == GLUT_KEY_LEFT && lastDirX == 0) dirX = -1, dirY = 0;
        else if (key == GLUT_KEY_RIGHT && lastDirX == 0) dirX = 1, dirY = 0;
    }
}

void my_keyboard(unsigned char key, int x, int y)
{
    if (gameOver && key == 'r') resetGame();
}

void update(int value)
{
    updateSnake();
    updateClouds();
    glutPostRedisplay();
     int delay = static_cast<int>(200 / snakeSpeed); // Higher snakeSpeed reduces the delay
    glutTimerFunc(delay, update, 0);
}

void myInit()
{
    glClearColor(16.0f / 255.0f, 207.0f / 255.0f, 12.0f / 255.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 700, 0, 700, -10, 10);
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("Snake Game");

    myInit();
    glutDisplayFunc(display);
    glutSpecialFunc(my_special_keyboard);
    glutKeyboardFunc(my_keyboard);
    glutTimerFunc(200, update, 0);
    glutMainLoop();
    return 0;
}
