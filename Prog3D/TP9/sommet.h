#ifndef SOMMET_H
#define SOMMET_H
#include <math.h>
#include "point.h"

class Sommet{
private:
	double x,y,z;
public:
	Sommet(Sommet* s){
		this->x = s->getX();
		this->y = s->getY();
		this->z = s->getZ();
	}

	Sommet(double x, double y,double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Sommet(Point* p){
		this->x = p->getX();
		this->y = p->getY();
		this->z = p->getZ();
	}

	double getX(){
		return this->x;
	}

	double getY(){
		return this->y;
	}

	double getZ(){
		return this->z;
	}

	bool equals(Sommet* s){
		return (this->getX()-s->getX()>-0.5 || this->getX()-s->getX()<0.5 &&
			this->getY()-s->getY()>-0.5 || this->getY()-s->getY()<0.5 &&
			this->getZ()-s->getZ()>-0.5 || this->getZ()-s->getZ()<0.5);
	}

	double getDist(Sommet* s){
		return sqrt(pow((s->getX()-this->getX()),2) +
					pow((s->getY()-this->getY()),2) +
					pow((s->getZ()-this->getZ()),2));
	}
};

#endif