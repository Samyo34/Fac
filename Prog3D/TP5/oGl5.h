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

bool intersectCyl(Point* p, Point* axisOrigin, Vector* axisVector, double rayon);

int voxelIntersectCyl(Voxel* v, Point* axisOrigin, Vector* axisVector, double rayon);

void octreeCyl(Voxel* v, Point* axisOrigin, Vector* axisVector, double rayon, double resolution);

void displayCylindreVolumic(Point* axisOrigin, Vector* axisVector, double rayon, double resolution);

void octreeInter(Voxel* v, Point* centreSphere, double rayonSph, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution);

void display_INTERSECTION_sphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOriginCyl, Vector* axisVectorCyl, double rayonCyl, double resolution);

void octreeSous(Voxel* v, Point* centreSphere,double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl,double resolution);

void display_SOUSTRACTION_sphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution);

void octreeUnion(Voxel* v, Point* centreSphere,double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl,double resolution);

void display_UNION_SphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution);