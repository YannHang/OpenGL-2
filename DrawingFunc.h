#pragma once
#include"glut.h"
#include<math.h>
#define Pi 3.141592653

void DrawCircRing(GLdouble Ox, GLdouble Oy, GLdouble Radius, GLint SpliceNum);

void DrawCircTrunCone(GLdouble Ox, GLdouble Oy, GLdouble RadiusUpper, GLdouble RadiusLower, GLdouble Height, GLint SpliceNum);

void DrawSphere(GLdouble Ox, GLdouble Oy, GLdouble Oz, GLdouble Radius, GLdouble LowerRange, GLdouble UpperRange, GLint LongtitudeSpliceNum, GLint LatitudeSpliceNum);

void DrawCircRing3D(GLdouble Ox, GLdouble Oy, GLdouble Oz, GLdouble RingRadius, GLdouble SectionRadius, GLdouble LowerRange, GLdouble UpperRange, GLint RingSpliceNum, GLint SectionSpliceNum);

void DrawSpring3D(GLdouble Sx, GLdouble Sy, GLdouble Sz, GLdouble SpringRadius, GLdouble Length, GLdouble Period, GLdouble Thickness, GLint SpringSpliceNum, GLint SectionSpliceNum);