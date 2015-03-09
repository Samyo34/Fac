#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"

Point** cylindre(Point* pointO, Point* pointD,long rayon, long hauteur, int nbMeridien);

void drawCylindre(Point** pts, long nbPoints);

Point** cone(Point* a, Point* b, long rayon, long hauteur, int nbMeridien);

void drawCone(Point** pts, long nbPoints);

Point*** sphere(Point* centre, long rayon, int nbMeridien, int nbPara);

void drawSphere(Point*** pts,int nbMeridien,int nbPara);