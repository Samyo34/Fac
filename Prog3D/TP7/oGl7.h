#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"

void drawSphere(Point*** pts,int nbMeridien,int nbPara);

Point*** sphere(Point* centre, long rayon, int nbMeridien, int nbPara);

void drawCylindre(Point*** pts, long nbPoints);

Point*** cylindre(Point* pointO,long rayon, long hauteur, int nbMeridien);