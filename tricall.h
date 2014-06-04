#ifndef _TRICALL_H
#define _TRICALL_H
#include <iostream>
#include <math.h>
#include "triangle.h"
#include "bubble.h"
using namespace std;
#define SpringK 0.005
#define Gravitation 0.1
#define  Pertime 0.02
#define  REAL double
void initIn(triangulateio &in,BubbleList p,REAL *Velocity,REAL* Mass);
void initOV(triangulateio &mid,triangulateio &vorout);

REAL GetDistance(REAL ax,REAL ay,REAL ex,REAL ey);
REAL GetSpring(REAL xi,REAL xj,REAL Lij);

REAL GetPlateauEqual(REAL ri,REAL rj);
REAL GetSlope(REAL ax,REAL ay,REAL ex,REAL ey);
int IsStable(REAL ax,REAL ay,REAL ra,REAL ex,REAL ey,REAL re);
void DynamicBubble(triangulateio &in,triangulateio &mid,REAL *Velocity,BubbleList bub,REAL *Mass);
void AddPoint(int *a,int point);
#endif
