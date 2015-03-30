#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sommet.h"

class Triangle{

private:
	Sommet* sommets[3];
public:
	Triangle(Sommet *s1, Sommet *s2, Sommet *s3){
		sommets[0]=s1;
		sommets[1]=s2;
		sommets[2]=s3;
	}

	Sommet** getSommets(){
		return sommets;
	}
};
#endif