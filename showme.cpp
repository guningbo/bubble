#include<windows.h>
#include<stdio.h>
#include<glaux.h>
#include<GL/glut.h>
#include <math.h>
#include "tricall.h"
#include "triangle.c"
#define  Pi 3.1415926


GLsizei  winWindth=700,winHeigh=700;
triangulateio in;
triangulateio mid;
triangulateio vorout;
REAL Velocity[1000]={0};
void init(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);

}

void DrawGraph(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.5);
	glEnd();
	glFlush();

}
void winReshapeFcn(int newWidth,int newHeigh)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void timeCircle(int num)
{
	DynamicBubble(in,mid,Velocity);
	initOV(mid,vorout);
	triangulate("pczAevn", &in, &mid, &vorout);	
	glutPostRedisplay();
	glutTimerFunc(50,timeCircle,1);
}
void DrawGLTCL()
{	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,1.0f);
	for(int pi=0;pi<in.numberofpoints;pi++)
	{
		REAL hx=in.pointlist[2*pi];
		REAL hy=in.pointlist[2*pi+1];
		REAL R=in.pointattributelist[pi];
	glBegin(GL_LINE_LOOP);
	
	for(int i=0; i<1000; ++i)
		glVertex2f(hx+R*cos(2*Pi/1000*i), hy+R*sin(2*Pi/1000*i));
	glEnd();
	}
	glColor3f(0.4f,0.0f,0.0f);
	for(int i=0;i<mid.numberoftriangles;i++)
	{
		GLdouble hx, hy, mx, my,ex,ey;
		hx=mid.pointlist[2*mid.trianglelist[i*3]];hy=mid.pointlist[2*mid.trianglelist[i*3]+1];
		mx=mid.pointlist[2*mid.trianglelist[i*3+1]];my=mid.pointlist[2*mid.trianglelist[i*3+1]+1];
		ex=mid.pointlist[2*mid.trianglelist[i*3+2]];ey=mid.pointlist[2*mid.trianglelist[i*3+2]+1];
		glBegin(GL_LINES);
		glVertex2f(hx,hy);
		glVertex2f(ex,ey);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(mx,my);
		glVertex2f(ex,ey);

		glEnd();
		glBegin(GL_LINES);
		glVertex2f(hx,hy);
		glVertex2f(mx,my);

		glEnd();
	;
	}	
	glFlush();

}
void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(winWindth,winHeigh);
	glutCreateWindow("bo");
	init();
	BubbleList bub;
	bub.Bubblelist();
	bub.Getpoint();
	initIn(in,bub);
	initOV(mid,vorout);
	triangulate("pczAevn", &in, &mid, &vorout);	
		glutDisplayFunc(DrawGLTCL);
	glutReshapeFunc(winReshapeFcn);
	glutTimerFunc(50,timeCircle,0);
	glutMainLoop();
}