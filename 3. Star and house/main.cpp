#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <ctime>
#define pi 3.142857
#include<iostream>
using namespace std;
void circle(float x1,float y1){
 float x=x1;
 float y=y1;
 float radius=45;
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

void drawStars(int numStars) {
    for (int i = 0; i < numStars; i++) {
        float x = (rand() % 500) ; // Random x within [-200, 200]
        float y = (rand() % 150+350) ; // Random y within [-200, 200]

        glPointSize(4);
        glBegin(GL_POINTS);
        glColor3ub(111, 111, 10); // Yellow color
        glVertex2f(x, y);
        glEnd();
    }
}
void house(float x, float y){



//Quads
glBegin(GL_QUADS);
glColor3ub(18,100,95);
glVertex2f( x,y ); //pivot x=30, y=40
glVertex2f( x+70, y );
glVertex2f( x+70, y+110);
glVertex2f( x, y+110);
glEnd();
//Quads
glBegin(GL_QUADS);
glColor3ub(118,10,195);
glVertex2f( x+25,y ); //pivot x=30, y=40
glVertex2f( x+45, y );
glVertex2f( x+45, y+80);
glVertex2f( x+25, y+80);
glEnd();
//Quads
glBegin(GL_QUADS);
glColor3ub(181,160,195);
glVertex2f( x+3,y+90 ); //pivot x=30, y=40
glVertex2f( x+13, y+90 );
glVertex2f( x+13, y+100);
glVertex2f( x+3, y+100);
glEnd();

//Triangle
glBegin(GL_TRIANGLES);
glColor3f(0,0,0);
glVertex2f( x-15,y+110 );
glVertex2f( x+85, y+110 );
glVertex2f( x+35, y+160);
glEnd();
}
void myInit ()
{

glClearColor(128.0f/255.0f,108.0f/255.0f, 148.0f/255.0f, 1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// setting window dimension in X- and Y- direction
glOrtho(0, 500, 0, 500, -10.0, 10.0);
}
void display ()
{
glClear(GL_COLOR_BUFFER_BIT);

srand(time(0));
    drawStars(200);
circle(250,400);
//Quads
glBegin(GL_QUADS);
glColor3ub(18,200,110);
glVertex2f( 0,0 );
glVertex2f( 500, 0 );
glVertex2f( 500, 350);
glVertex2f( 0, 350);
glEnd();
house(30,40);
house(220,40);
house(400,40);
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
