#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "point.h"
#include "vector.h"
#include "triangle.h"
#include "sommet.h"

#include <fstream>
#include <sstream>

Point** makeCube();

void readFile(char* fileName);

void affiche();

double* getVal(std::vector<std::string> ligne);

int** getVoisins();

void fusion(Point* p1,Point* p2);

Triangle** raffinement(Triangle* triangle);

void raffineAll();

//vector<string> split(string ligne);