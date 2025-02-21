#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;


void myInit ()
{
//glClearColor(0.0, 1.0, 0.0, 0.0);
//glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);
//glColor3f(0.0, 0.2, 0.0);
glClearColor(255.0f/255.0f,255.0f/255.0f, 255.0f/255.0f, 1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// setting window dimension in X- and Y- direction
glOrtho(0, 500, 0, 500, -10.0, 10.0);
}

void flower(float x, float y){

    glBegin(GL_TRIANGLES);
glColor3ub(150,228,169);
glVertex2f( x,y );//pivot x=252, y=200
glVertex2f( x+50, y );
glVertex2f( x+25, y+50);


glEnd();
glBegin(GL_TRIANGLES);
glColor3ub(250,228,69);
glVertex2f( x+10,y );//pivot x=250, y=250
glVertex2f( x, y );
glVertex2f( x-50, y-50);
glEnd();

glBegin(GL_TRIANGLES);
glColor3ub(250,228,69);
glVertex2f( x+40,y );//pivot x=250, y=250
glVertex2f( x+50, y );
glVertex2f( x+100, y-50);
glEnd();

glBegin(GL_TRIANGLES);
glColor3ub(250,228,69);
glVertex2f( x+20,y+45 );//pivot x=250, y=250
glVertex2f( x+30, y+45 );
glVertex2f( x+25, y+120);
glEnd();
glBegin(GL_TRIANGLES);
glColor3ub(250,228,69);
glVertex2f( x+10,y+20 );//pivot x=250, y=250
glVertex2f( x+20, y+30 );
glVertex2f( x-50, y+50);
glEnd();

glBegin(GL_TRIANGLES);
glColor3ub(250,228,69);
glVertex2f( x+40,y+20 );//pivot x=250, y=250
glVertex2f( x+100, y+50 );
glVertex2f( x+30, y+30);
glEnd();

}
void display ()
{
glClear(GL_COLOR_BUFFER_BIT);
flower(252,200);

glFlush();
}
void my_keyboard(unsigned char key, int x, int y)
{
 cout<<key<<endl;
}
void update(int value) {
 //moonY=moonY+0.9;
//cout<<moonY<<endl;
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
