#include "voxel.h"

void displayVoxel(Point* centre, long length){
	Point* p1 = new Point(-(length/2),length/2,length/2);
	Point* p2 = new Point(length/2,length/2,length/2);
	Point* p3 = new Point(length/2,-(length/2),length/2);
	Point* p4 = new Point(-(length/2),-(length/2),length/2);

	Point* p5 = new Point(-(length/2),length/2,-length/2);
	Point* p6 = new Point(length/2,length/2,-length/2);
	Point* p7 = new Point(length/2,-(length/2),-length/2);
	Point* p8 = new Point(-(length/2),-(length/2),-length/2);
	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glEnd();
}

