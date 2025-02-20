#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;
float ballX=100;
float ballY=480;
float velocity = -3;   // Initial upwards velocity
float gravity = -0.5;
float dfactor = 0.4;



void ball(float x1,float y1){
 float x=x1;
 float y=y1;
 float radius=15;
 double pii=3.1416;
 glBegin(GL_TRIANGLE_FAN);
 glColor3ub(2,19,4);
 glVertex2f( x,y );
 for(int i=0;i<=360;i++){ ///i=0,1,2 360
 glColor3ub(11,17,4);
 float a=x+radius*cos(i*(pii/180));
 float b=y+radius*sin(i*(pii/180));
 glVertex2f( a,b);
 }
 glEnd();
}



void myInit ()
{

glClearColor(110.0f/255.0f, 13.0f/255.0f, 8.0f/255.0f, 1.0f);
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
ballX+=0.5;
    if (ballY < 15) {
    velocity = -velocity * dfactor;
    ballY = 15;
}

if (ballY > 485) {
    velocity = -velocity * dfactor;
    ballY = 485;
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
