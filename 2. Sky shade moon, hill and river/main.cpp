#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;
void circle(float x1,float y1){
 float x=x1;
 float y=y1;
 float radius=50;
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

void pahar(float x,float y){
    //Triangle
glBegin(GL_TRIANGLES);
glColor3ub(25,220,20);
glVertex2f( x,y );//pivot x=20, y=200
glVertex2f( x+40, y );
glVertex2f( x+25, y+120);
glEnd();
glBegin(GL_TRIANGLES);
glColor3ub(15,180,150);
glVertex2f( x-20,y );
glVertex2f( x+25, y );
glVertex2f( x-5, y+90);
glEnd();
glBegin(GL_TRIANGLES);
glColor3ub(145,230,110);
glVertex2f( x-40,y );
glVertex2f( x,y );
glVertex2f( x-15, y+70);
glEnd();
}
void myInit ()
{
//glClearColor(0.0, 1.0, 0.0, 0.0);
//glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);
//glColor3f(0.0, 0.2, 0.0);
glClearColor(128.0f/255.0f,0, 0, 1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// setting window dimension in X- and Y- direction
glOrtho(0, 500, 0, 500, -10.0, 10.0);
}
void display ()
{
glClear(GL_COLOR_BUFFER_BIT);
//Akash
glBegin(GL_QUADS);
glColor3ub(22,54,92);
glVertex2f( 0,0 );
glColor3ub(24,0,92);
glVertex2f( 500, 0 );
glColor3ub(27,50,95);
glVertex2f( 500, 500);
glColor3ub(20,60,88);
glVertex2f( 0, 500);
glEnd();
//Akash
glBegin(GL_QUADS);
glColor3ub(222,54,192);
glVertex2f( 0,0 );
glVertex2f( 500, 0 );
glVertex2f( 500, 250);
glVertex2f( 0, 250);
glEnd();
circle(240,380);
pahar(20,230);
pahar(50,230);
pahar(110,230);
pahar(150,230);
pahar(200,230);
pahar(250,230);
pahar(320,230);
pahar(380,230);
pahar(440,230);
pahar(460,230);


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
//Quads
glBegin(GL_QUADS);
glColor3ub(128,0,0);
glVertex2f( 0,0 );
glVertex2f( 200, 0 );
glVertex2f( 200, 200);
glVertex2f( 0, 200);
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

glutMainLoop();
}
