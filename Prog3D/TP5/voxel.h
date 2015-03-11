#ifndef VOXEL_H
#define VOXEL_H

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "../TP4/point.h"
#include "../TP4/vector.h"
#include "../TP4/oGl3.h"
#include "../TP4/figureGl.h"

class Voxel{
private:
	Point* centre;
	double length;
	 
	Voxel** sousVox;
public:
	//Voxel(Point* p1,Point* p2, Point* p3, Point* p4, Point* p5, Point* p6, Point* p7);
	Voxel(Point* centre, double length);
	void setSousVoxel(Voxel** voxs, long nbVox);
	Voxel** getSousVoxel();
	Point** getCube();
};
#endif

//void diplayVoxel(Point* centre, double length);