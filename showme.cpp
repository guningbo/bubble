#include<windows.h>
#include<stdio.h>
#include<glaux.h>
#include<GL/glut.h>
#include <math.h>
#include "tricall.h"
#include "triangle.c"
#define  Pi 3.1415926
#define MaxSize 1.0

GLsizei  winWindth=700,winHeigh=700;
triangulateio in;
triangulateio mid;
triangulateio vorout;
BubbleList bub;
REAL Velocity[2000]={0};
REAL Mass[1000]={0};
void init(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-MaxSize,MaxSize,-MaxSize,MaxSize);

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
	gluOrtho2D(-MaxSize,MaxSize,-MaxSize,MaxSize);
	glClear(GL_COLOR_BUFFER_BIT);
}

void timeCircle(int num)
{
	DynamicBubble(in,mid,Velocity,bub,Mass);
	initOV(mid,vorout);
	triangulate("pczAevn", &in, &mid, &vorout);	
	glutPostRedisplay();
	glutTimerFunc(50,timeCircle,1);
}
void timeAddPoint(int num)
{  BUBBLE* p=new BUBBLE;
	p=bub.GetHead();
	int i=0;
	p=p->next;
	while(p!=NULL){
		
	p->Velocity[0]=Velocity[2*i];
	p->Velocity[1]=Velocity[2*i+1];
	p->pointX=in.pointlist[2*i];
	p->pointY=in.pointlist[2*i+1];
	i++;
	p=p->next;
	}	
	bub.popPoint();
	bub.AddPoint();
free(in.pointlist);
free(in.pointattributelist);
free(in.pointmarkerlist);
free(in.regionlist);
free(in.trianglelist);
free(in.triangleattributelist);
free(in.neighborlist);
free(in.segmentlist);
free(in.segmentmarkerlist);
free(in.edgelist);
free(in.edgemarkerlist);
free(mid.pointlist);
free(mid.pointattributelist);
free(mid.pointmarkerlist);
free(mid.trianglelist);
free(mid.triangleattributelist);
free(mid.trianglearealist);
free(mid.neighborlist);
free(mid.segmentlist);
free(mid.segmentmarkerlist);
free(mid.edgelist);
free(mid.edgemarkerlist);
free(vorout.pointlist);
free(vorout.pointattributelist);
free(vorout.edgelist);
free(vorout.normlist);

initIn(in,bub,Velocity,Mass);
initOV(mid,vorout);
triangulate("pczAevn", &in, &mid, &vorout);
glutTimerFunc(2000,timeAddPoint,1);
}


void DrawGLTCL()
{	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,1.0f);
	for(int pi=0;pi<mid.numberofpoints;pi++)
	{
		REAL hx=mid.pointlist[2*pi];
		REAL hy=mid.pointlist[2*pi+1];
		REAL R=mid.pointattributelist[pi];
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<1000; ++i)
		glVertex2f(hx+R*cos(2*Pi/1000*i), hy+R*sin(2*Pi/1000*i));
	glEnd();
	}
/*	glColor3f(0.4f,0.0f,0.0f);
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
	
	}	
	glColor3f(0.0f,0.4f,0.3f);
	
	for(int i=0;i<vorout.numberofedges;i++)
	{
		GLdouble hx, hy,ex,ey;
		hx=vorout.pointlist[2*vorout.edgelist[2*i]];
		hy=vorout.pointlist[2*vorout.edgelist[2*i]+1];
		if(vorout.edgelist[2*i+1]!=-1)
		{	
			ex=vorout.pointlist[2*vorout.edgelist[2*i+1]];
			ey=vorout.pointlist[2*vorout.edgelist[2*i+1]+1];
		}
		else
		{
			ex=vorout.pointlist[2*vorout.edgelist[2*i]]+10*vorout.normlist[2*i];
			ey=vorout.pointlist[2*vorout.edgelist[2*i]+1]+10*vorout.normlist[2*i+1];	
			
		}
		glBegin(GL_LINES);
		glVertex2f(hx,hy);
		glVertex2f(ex,ey);
		glEnd();
	}
	*/
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
	bub.Bubblelist();
	bub.Getpoint();
	initIn(in,bub,Velocity,Mass);
	initOV(mid,vorout);
	triangulate("pczAevn", &in, &mid, &vorout);	
	glutDisplayFunc(DrawGLTCL);
	glutReshapeFunc(winReshapeFcn);
	glutTimerFunc(1000,timeAddPoint,0);
	glutTimerFunc(50,timeCircle,0);


	glutMainLoop();
}