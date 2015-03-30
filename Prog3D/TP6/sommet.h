#ifndef SOMMET_H
#define SOMMET_H

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

	double getX(){
		return this->x;
	}

	double getY(){
		return this->y;
	}

	double getZ(){
		return this->z;
	}
};

#endif