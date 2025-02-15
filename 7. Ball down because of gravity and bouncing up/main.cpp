#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;
float ballX=250;
float ballY=480;
float velocity = -3;   // Initial upwards velocity
float gravity = -0.5;  // Reduced gravity for smoother motion
float dfactor = 0.7;   // Energy retained after bounce (70%)



void ball(float x1,float y1){
 float x=x1;
 float y=y1;
 float radius=15;
 double pii=3.1416;
 glBegin(GL_TRIANGLE_FAN);
 glColor3ub(222,219,214);
 glVertex2f( x,y );
 for(int i=0;i<=360;i++){ ///i=0,1,2 360
 glColor3ub(181,178,174);
 float a=x+radius*cos(i*(pii/180));
 float b=y+radius*sin(i*(pii/180));
 glVertex2f( a,b);
 }
 glEnd();
}



void myInit ()
{

glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// setting window dimension in X- and Y- direction
glOrtho(0, 500, 0, 500, -10.0, 10.0);
}
void display ()
{
glClear(GL_COLOR_BUFFER_BIT);
  ball(ballX, ballY);

glFlush();
}
void my_keyboard(unsigned char key, int x, int y)
{
 cout<<key<<endl;
 if(key=='a'){
    ballY+=20;
 }
 else if(key=='b'){
    ballX-=10;
 }

}



void update(int value) {
    velocity+=gravity;
ballY+=velocity;
    if (ballY < 15) {  // If the ball touches the bottom
    velocity = -velocity * dfactor;  // Reverse velocity with damping
    ballY = 15;  // Ensure it doesn't go below this point
}

if (ballY > 485) {  // If the ball touches the top
    velocity = -velocity * dfactor;  // Reverse direction
    ballY = 485;  // Prevent it from going out of bounds
}



glutPostRedisplay();
glutTimerFunc(25, update, 0);
}


int main (int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// giving window size in X- and Y- direction
glutInitWindowSize(500, 500);
glutInitWindowPosition(100, 0);
// Giving name to window
glutCreateWindow("bahubali 3");
myInit();
 glutDisplayFunc(display);
 glutKeyboardFunc(my_keyboard);
glutTimerFunc(25, update, 0);
//glutTimerFunc(25, update, 0);
glutMainLoop();
}
