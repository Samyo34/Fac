#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "point.h"
#include "vector.h"
#include "triangle.h"
#include <fstream>
#include <sstream>

#define PI 3.14159265

void drawSphere(Point*** pts,int nbMeridien,int nbPara);

Point*** sphere(Point* centre, long rayon, int nbMeridien, int nbPara);

void drawCylindre(Point*** pts, long nbPoints);

Point*** cylindre(Point* pointO,long rayon, long hauteur, int nbMeridien);

double getAngleDiedre(Triangle* triangle1, Triangle* triangle2);

void readFile(char* fileName);

//std::vector<string> split(std::string ligne);

//double* getVal(std::vector<string> ligne);

void areteVive(double seuil);