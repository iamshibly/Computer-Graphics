#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> // For std::find
#include <cstdio>    // For printf

// Screen dimensions
const int screenWidth = 800;
const int screenHeight = 600;

// Grid size
const int gridSize = 20;
const int gridWidth = screenWidth / gridSize;
const int gridHeight = screenHeight / gridSize;

// Directions
enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = RIGHT;

// Snake and food
std::vector<std::pair<int, int>> snake = {{5, 5}, {4, 5}, {3, 5}};
std::pair<int, int> food;
bool gameOver = false;
int score = 0;

// Function to spawn food at a random location
void spawnFood() {
    food.first = rand() % gridWidth;
    food.second = rand() % gridHeight;
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    srand(static_cast<unsigned int>(time(0))); // Seed for random numbers
    spawnFood(); // Spawn initial food
}

// Draw a square block
void drawSquare(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x * gridSize, y * gridSize);
    glVertex2f((x + 1) * gridSize, y * gridSize);
    glVertex2f((x + 1) * gridSize, (y + 1) * gridSize);
    glVertex2f(x * gridSize, (y + 1) * gridSize);
    glEnd();
}

// Render the game screen
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the snake
    for (const auto& segment : snake) {
        drawSquare(segment.first, segment.second, 0.0f, 1.0f, 0.0f); // Green color
    }

    // Draw the food
    drawSquare(food.first, food.second, 1.0f, 0.0f, 0.0f); // Red color

    glutSwapBuffers();
}

// Update the game state
void update(int value) {
    if (gameOver) return;

    // Move the snake
    std::pair<int, int> newHead = snake.front();
    switch (dir) {
        case UP:    newHead.second++; break;
        case DOWN:  newHead.second--; break;
        case LEFT:  newHead.first--; break;
        case RIGHT: newHead.first++; break;
    }

    // Check for collisions
    if (newHead.first < 0 || newHead.second < 0 ||
        newHead.first >= gridWidth || newHead.second >= gridHeight ||
        std::find(snake.begin(), snake.end(), newHead) != snake.end()) {
        gameOver = true;
        printf("Game Over! Final Score: %d\n", score);
        return;
    }

    // Add the new head to the snake
    snake.insert(snake.begin(), newHead);

    // Check if the snake eats the food
    if (newHead == food) {
        score++;
        spawnFood();
    } else {
        // Remove the tail if no food eaten
        snake.pop_back();
    }

    // Request a redraw and set up the next update
    glutPostRedisplay();
    glutTimerFunc(100, update, 0); // Schedule next update
}

// Handle keyboard input
void keyboard(int key, int x, int y) {
    if (gameOver) return;

    switch (key) {
        case GLUT_KEY_UP:    if (dir != DOWN) dir = UP; break;
        case GLUT_KEY_DOWN:  if (dir != UP) dir = DOWN; break;
        case GLUT_KEY_LEFT:  if (dir != RIGHT) dir = LEFT; break;
        case GLUT_KEY_RIGHT: if (dir != LEFT) dir = RIGHT; break;
    }
}

// Handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height); // Set up a 2D orthographic view
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Snake Game");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, update, 0); // Start the game loop

    glutMainLoop();
    return 0;
}
