#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;
float carX= 10;
float carY= 10;
//float carX=230;
//float carY=450;
void circle(float x1,float y1){
 float x=x1;
 float y=y1;
 float radius=6;
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
void car(float x, float y){

    //Quads
glBegin(GL_QUADS);
glColor3ub(128,0,0);
glVertex2f( x,y );//pivot x=10, y=250 or x=230, y=450
glVertex2f( x+40, y );
glVertex2f( x+40, y+30);
glVertex2f( x, y+30);
glEnd();
//Quads
glBegin(GL_QUADS);
glColor3ub(158,10,20);
glVertex2f( x+5,y+30 );
glVertex2f( x+35, y+30 );
glVertex2f( x+25, y+45);
glVertex2f( x+10, y+45);
glEnd();

circle(x+10,y);
circle(x+32,y);

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
  car(carX, carY);

glFlush();
}
void my_keyboard(unsigned char key, int x, int y)
{
 cout<<key<<endl;
 if(key=='a'){
    carY+=20;
 }
 else if(key=='b'){
    carX-=10;
 }

}

//up to down bari kheye again up again bari kheye down repaet
//int direction =1;
//void update(int value) {
//    carY-=3*direction;
//    if(carY< 0){
//        direction=-1;
//    }
//    else if(carY>455){
//        direction=1;
//    }
//
//glutPostRedisplay();
//glutTimerFunc(25, update, 0);
//}

//dane and bame bari kheye left to right and right to left
//int direction = 1; // 1 for right, -1 for left
//
//void update(int value) {
//    carX += 2 * direction;
//
//    if (carX >= 470) {
//        direction = -1; // Change direction to left
//    } else if (carX <= 0) {
//        direction = 1; // Change direction to right
//    }
//    glutPostRedisplay();
//    glutTimerFunc(25, update, 0);
//}

//gari bottom left to top right and top right to bottom left
int direction = 1;
void update(int value) {
    carX += 2 * direction;
    carY += 2 * direction;

    if (carY >= 450 || carX >= 460 ) {

        direction = -1; // Change direction to left
    } else if (carY <= 5 || carX <= 0) {

        direction = 1; // Change direction to right
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
