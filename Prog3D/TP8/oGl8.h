#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "point.h"
#include "vector.h"
#include "../TP4/oGl3.h"
#include "../TP4/figureGl.h"
#include "triangle.h"

#include <fstream>
#include <sstream>


void readFile(char* fileName);

void affiche();

double* getVal(std::vector<std::string> ligne);

int** getVoisins();