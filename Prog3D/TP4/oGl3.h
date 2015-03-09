#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"
#include "oGl.h"

Point** surf_cyle(Point ** tabPointOfCurve, long nbPointsCourbe, Point ** ab, long nbPointDroite);

void drawSurf(Point** tabPointOfCurve, long nbPoint);

Point** BezierSurfaceByCasteljau(Point** tabControlPointU, long nbControlPointU, long nbU,Point** tabControlPointV, long nbControlPointV,long nbV);