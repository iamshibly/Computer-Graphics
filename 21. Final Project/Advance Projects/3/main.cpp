#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

const int screenWidth = 800;
const int screenHeight = 600;
const int gridSize = 20;
const int gridWidth = screenWidth / gridSize;
const int gridHeight = screenHeight / gridSize;
const int skyHeight = 400;
const int playableGridHeight = skyHeight / gridSize;

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = RIGHT;

struct Tree {
    float x, y;
    float scale;
};

std::vector<std::pair<int, int>> snake = {{5, 5}, {4, 5}, {3, 5}};
std::vector<Tree> trees;
std::pair<int, int> food;
bool gameOver = false;
int score = 0;
struct Bird {
    float x, y;   // Position
    float size;   // Size of the bird
};

struct Cloud {
    float x, y;   // Position
    float width, height; // Size of the cloud
};

Bird bird;
std::vector<Cloud> clouds;


void drawCircle(float cx, float cy, float r, int segments = 30) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawTree(float x, float y, float scale) {
    // Trunk
    glColor3f(64.0f/255.0f, 44.0f/255.0f, 31.0f/255.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 5*scale, y);
    glVertex2f(x + 5*scale, y);
    glVertex2f(x + 5*scale, y + 30*scale);
    glVertex2f(x - 5*scale, y + 30*scale);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.4f, 0.0f);
    float leafHeight = 40*scale;
    float leafWidth = 30*scale;

    glBegin(GL_TRIANGLES);
    glVertex2f(x - leafWidth, y + 20*scale);
    glVertex2f(x + leafWidth, y + 20*scale);
    glVertex2f(x, y + 20*scale + leafHeight);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - leafWidth*0.8f, y + 40*scale);
    glVertex2f(x + leafWidth*0.8f, y + 40*scale);
    glVertex2f(x, y + 40*scale + leafHeight);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - leafWidth*0.6f, y + 60*scale);
    glVertex2f(x + leafWidth*0.6f, y + 60*scale);
    glVertex2f(x, y + 60*scale + leafHeight*0.8f);
    glEnd();
}

void drawBackground() {
    // Sky
    glColor3f(135.0f/255.0f, 206.0f/255.0f, 235.0f/255.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 400);
    glVertex2f(800, 400);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();

    // Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(700, 500, 30);
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(700, 500, 25);

    // Green grass background
    glColor3f(14.0f/255.0f, 237.0f/255.0f, 74.0f/255.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, 400);
    glVertex2f(0, 400);
    glEnd();

    // Earth-colored trapezoid
    glColor3f(139.0f/255.0f, 69.0f/255.0f, 19.0f/255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glVertex2f(700, 200);
    glVertex2f(0, 100);
    glEnd();

    // Brown circle
    glColor3f(139.0f/255.0f, 69.0f/255.0f, 19.0f/255.0f);
    drawCircle(690, 185, 17);

    // Draw trees
    for(const auto& tree : trees) {
        drawTree(tree.x, tree.y, tree.scale);
    }
}

void drawApple(int x, int y) {
    float cx = (x + 0.5f) * gridSize;
    float cy = (y + 0.5f) * gridSize;
    float radius = gridSize / 2.0f;

    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(cx, cy, radius);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    drawCircle(cx - radius/3, cy + radius/3, radius/4);

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(cx - 2, cy + radius);
    glVertex2f(cx + 2, cy + radius);
    glVertex2f(cx + 2, cy + radius + 8);
    glVertex2f(cx - 2, cy + radius + 8);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx + 2, cy + radius + 4);
    glVertex2f(cx + 10, cy + radius + 8);
    glVertex2f(cx + 2, cy + radius + 8);
    glEnd();
}

void drawSnakeSegment(float x, float y, bool isHead) {
    float cx = (x + 0.5f) * gridSize;
    float cy = (y + 0.5f) * gridSize;
    float radius = gridSize / 2.0f * 1.0f;

    glColor3f(0.0f, 0.5f, 0.0f);
    drawCircle(cx, cy, radius);

    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(cx, cy, radius * 0.8f);

    if (isHead) {
        glColor3f(1.0f, 1.0f, 1.0f);
        float eyeOffset = radius * 0.3f;
        drawCircle(cx + eyeOffset, cy + eyeOffset, radius * 0.2f);
        drawCircle(cx - eyeOffset, cy + eyeOffset, radius * 0.2f);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawCircle(cx + eyeOffset, cy + eyeOffset, radius * 0.1f);
        drawCircle(cx - eyeOffset, cy + eyeOffset, radius * 0.1f);
    }
}

void generateTrees() {
    trees.clear();
    int numTrees = rand() % 6 + 10; // Generate between 10 and 15 trees (10 minimum)

    for (int i = 0; i < numTrees; i++) {
        Tree tree;
        tree.x = rand() % screenWidth;          // Random x-coordinate
        tree.y = rand() % (skyHeight - 100);   // Random y-coordinate within a limited range
        tree.scale = (float)(rand() % 50 + 50) / 100.0f; // Scale between 0.5 and 1.0
        trees.push_back(tree);
    }
}


void spawnFood() {
    if (trees.empty()) return; // Ensure trees are generated before spawning food

    // Select a random tree
    const Tree& randomTree = trees[rand() % trees.size()];

    // Define leaf boundaries based on the tree's position and scale
    float leafWidth = 30 * randomTree.scale;
    float leafHeight = 40 * randomTree.scale;
    float leafBaseY = randomTree.y + 20 * randomTree.scale;

    // Generate a random position within the tree's leaf boundaries
    float leafX = randomTree.x + ((rand() % 2 == 0 ? -1 : 1) * (rand() % static_cast<int>(leafWidth)));
    float leafY = leafBaseY + (rand() % static_cast<int>(leafHeight));

    // Map the position to grid coordinates
    int gridX = static_cast<int>(leafX / gridSize);
    int gridY = static_cast<int>(leafY / gridSize);

    // Ensure grid coordinates are within bounds and don't overlap with the snake
    while ((gridX < 0 || gridX >= gridWidth || gridY < 0 || gridY >= playableGridHeight) ||
           std::find(snake.begin(), snake.end(), std::make_pair(gridX, gridY)) != snake.end()) {
        // Retry randomization if position is invalid
        leafX = randomTree.x + ((rand() % 2 == 0 ? -1 : 1) * (rand() % static_cast<int>(leafWidth)));
        leafY = leafBaseY + (rand() % static_cast<int>(leafHeight));
        gridX = static_cast<int>(leafX / gridSize);
        gridY = static_cast<int>(leafY / gridSize);
    }

    // Assign the valid position to food
    food.first = gridX;
    food.second = gridY;
}

void drawBird(float x, float y, float size) {
    // Draw bird body (extremely slim ellipse)
    glColor3f(1.0f, 0.9f, 0.4f); // Light yellow body
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * size * 0.2f, y + sin(angle) * size * 1.8f); // Extremely slim and tall body
    }
    glEnd();

    // Draw bird wings (smaller curved ellipses)
    glColor3f(1.0f, 0.7f, 0.2f); // Orange wings
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * size * 1.0f - size * 0.1f, y + sin(angle) * size * 0.8f); // Slimmer left wing
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * size * 1.0f + size * 0.1f, y + sin(angle) * size * 0.8f); // Slimmer right wing
    }
    glEnd();

    // Draw bird tail (slightly slimmer triangle)
    glColor3f(1.0f, 0.6f, 0.0f); // Dark orange tail
    glBegin(GL_TRIANGLES);
    glVertex2f(x - size * 1.8f, y);                  // Extended tip of the tail
    glVertex2f(x - size * 1.0f, y + size * 0.6f);    // Slimmer top
    glVertex2f(x - size * 1.0f, y - size * 0.6f);    // Slimmer bottom
    glEnd();

    // Draw bird beak (smaller triangle)
    glColor3f(1.0f, 0.5f, 0.0f); // Dark orange for the beak
    glBegin(GL_TRIANGLES);
    glVertex2f(x + size * 0.9f, y);                   // Tip of the beak
    glVertex2f(x + size * 0.6f, y + size * 0.15f);    // Top
    glVertex2f(x + size * 0.6f, y - size * 0.15f);    // Bottom
    glEnd();

    // Draw bird eye (slim circle)
    glColor3f(0.0f, 0.0f, 0.0f); // Black for the eye
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + size * 0.4f + cos(angle) * size * 0.1f, y + sin(angle) * size * 0.1f); // Slimmer eye
    }
    glEnd();

    // Draw bird pupil (small circle inside eye)
    glColor3f(1.0f, 1.0f, 1.0f); // White for the pupil
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + size * 0.4f + cos(angle) * size * 0.03f, y + sin(angle) * size * 0.03f); // Smaller pupil
    }
    glEnd();
}

void drawCloud(float x, float y, float width, float height) {
    glColor3f(1.0f, 1.0f, 1.0f);

    // Main cloud body
    drawCircle(x, y, width / 3);
    drawCircle(x - width / 4, y, width / 4);
    drawCircle(x + width / 4, y, width / 4);
    drawCircle(x, y + height / 4, width / 4);
}



void init() {
    glClearColor(14.0f / 255.0f, 237.0f / 255.0f, 74.0f / 255.0f, 1.0f);
    srand(static_cast<unsigned int>(time(0)));

    // Bird initialization
    bird.x = -50; // Start off-screen
    bird.y = screenHeight - 100; // Near the top
    bird.size = 20; // Size of the bird

    // Clouds initialization
    clouds.clear();
    for (int i = 0; i < 3; i++) {
        Cloud cloud;
        cloud.x = rand() % screenWidth;
        cloud.y = rand() % (screenHeight - skyHeight) + skyHeight; // Ensure clouds are within the sky region
        cloud.width = rand() % 80 + 40; // Random width
        cloud.height = rand() % 30 + 20; // Random height
        clouds.push_back(cloud);
    }

    generateTrees();
    spawnFood();
}

void update(int value) {
    if (gameOver) return;

    // Snake movement logic
    std::pair<int, int> newHead = snake.front();
    switch (dir) {
        case UP:    newHead.second++; break;
        case DOWN:  newHead.second--; break;
        case LEFT:  newHead.first--; break;
        case RIGHT: newHead.first++; break;
    }

    if (newHead.first < 0 || newHead.second < 0 ||
        newHead.first >= gridWidth || newHead.second >= playableGridHeight ||
        std::find(snake.begin(), snake.end(), newHead) != snake.end()) {
        gameOver = true;
        printf("Game Over! Final Score: %d\n", score);
        return;
    }

    snake.insert(snake.begin(), newHead);

    if (newHead == food) {
        score++;
        spawnFood();
    } else {
        snake.pop_back();
    }

    bird.x += 2.0f;
    if (bird.x > screenWidth + bird.size) {
        bird.x = -50; // Reset position to the left of the screen
        bird.y = screenHeight - 100 - rand() % 100; // Randomize height
    }

    // Cloud movement
    for (auto& cloud : clouds) {
        cloud.x -= 1.0f; // Move left
        if (cloud.x < -cloud.width) {
            cloud.x = screenWidth; // Reset position to the right of the screen
            cloud.y = rand() % (screenHeight - skyHeight) + skyHeight; // Keep clouds in the sky region
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();

    // Draw moving clouds
    for (const auto& cloud : clouds) {
        drawCloud(cloud.x, cloud.y, cloud.width, cloud.height);
    }

    // Draw the bird
    drawBird(bird.x, bird.y, bird.size);

    for (size_t i = 0; i < snake.size(); i++) {
        drawSnakeSegment(snake[i].first, snake[i].second, i == 0);
    }

    drawApple(food.first, food.second);

    glColor3f(0.0f, 0.2f, 0.0f);
    glRasterPos2f(10, screenHeight - 20);
    char scoreStr[30];
    sprintf(scoreStr, "Score: %d", score);
    for (char* c = scoreStr; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(screenWidth / 2 - 50, screenHeight / 2);
        const char* text = "Game Over!";
        for (const char* c = text; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    glutSwapBuffers();
}




void keyboard(int key, int x, int y) {
    if (gameOver) return;
    switch (key) {
        case GLUT_KEY_UP:    if (dir != DOWN) dir = UP; break;
        case GLUT_KEY_DOWN:  if (dir != UP) dir = DOWN; break;
        case GLUT_KEY_LEFT:  if (dir != RIGHT) dir = LEFT; break;
        case GLUT_KEY_RIGHT: if (dir != LEFT) dir = RIGHT; break;
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Snake Game");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, update, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();
    return 0;
}
