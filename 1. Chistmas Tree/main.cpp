#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;

void trees(float x, float y){
    //Wood
glBegin(GL_QUADS);
glColor3ub(100,112,30);
glVertex2f( x,y );// pivt x=30, y=250
glVertex2f( x+30, y );
glVertex2f( x+30, y+70);
glVertex2f( x, y+70);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(10,50,200);
glVertex2f( x-20,y+70 );
glVertex2f( x+50, y+70 );
glVertex2f( x+15, y+130);
glEnd();
glBegin(GL_TRIANGLES);
glColor3f(10,50,200);
glVertex2f( x-10,y+100 );
glVertex2f( x+45, y+100 );
glVertex2f( x+15, y+140);
glEnd();
glBegin(GL_TRIANGLES);
glColor3f(10,50,200);
glVertex2f( x-5,y+120 );
glVertex2f( x+40, y+120 );
glVertex2f( x+15, y+160);
glEnd();



}
void myInit ()
{

glClearColor(128.0f/255.0f,0, 0, 1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// setting window dimension in X- and Y- direction
glOrtho(0, 500, 0, 500, -10.0, 10.0);
}
void display ()
{
glClear(GL_COLOR_BUFFER_BIT);
//Triangle


//Quads
glBegin(GL_QUADS);
glColor3ub(200,12,130);
glVertex2f( 0,0 );
glVertex2f( 500, 0 );
glVertex2f( 500, 250);
glVertex2f( 0, 250);
glEnd();
trees(30,250);
trees(230,250);
trees(440,250);
/*
//lines
glBegin(GL_LINES);
glColor3f(0,1,0);
glVertex2f( 250,500 );
glVertex2f( 250, 0 );
glEnd();
//point
glPointSize(100);
glBegin(GL_POINTS);
glColor3f(0,1,0);
glVertex2f( 100,100 );
glEnd();

//polygon
glBegin(GL_POLYGON);
glColor3f(0,1,0);
glVertex2f( 100,100 );
glVertex2f( 100, 0 );
glVertex2f( 50, 0 );
glVertex2f( 10, 50 );
glVertex2f( 50, 200 );
glEnd();
*/
glFlush();
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

//glutTimerFunc(25, update, 0);
glutMainLoop();
}
