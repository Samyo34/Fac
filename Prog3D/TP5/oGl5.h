#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"
#include "../TP4/oGl3.h"
#include "../TP4/figureGl.h"

void displayVoxel(Point* centre, double length);

void displaySphereVolumic(Point* centre,double rayon, double resolution);

bool intersect(Point* point, Point* centre, double rayon, int nbPoints);

int voxelIntersect(Voxel* v, Point* centre, double rayon);

void octree(Voxel* v, Point* centre, double rayon, double resolution);