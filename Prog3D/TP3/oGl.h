#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"

void drawCurve(Point** tabPointOfCurve, long nbPoint);

Point** HermiteCubicCurve(Point *p0, Point *p1, Vector *v0, Vector *v1, long nbU);

Point ** BezierCurveByBernstein(Point** tabControlPoint, long nbControlPoint, long nbU);

Point** BezierCurveByCasteljau(Point** tabControlPoint, long nbControlPoint, long nbU);

Point* calc(Point** tabControlPoint, long nbControlPoint, float u);

long fact(long nb);
