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

	bool isVoisin(Triangle* tr){
		Sommet** sommet1 = this->getSommets();
		Sommet** sommet2 = tr->getSommets();

		if(sommet1[0]->getDist(sommet1[1]) == sommet2[0]->getDist(sommet2[1])){

			return ((sommet1[0]->equals(sommet2[0]) && sommet1[1]->equals(sommet2[1])) ||
				((sommet1[0]->equals(sommet2[1]) && sommet1[1]->equals(sommet2[0]))));

		}else if(sommet1[1]->getDist(sommet1[2]) == sommet2[1]->getDist(sommet2[2])){

			return ((sommet1[1]->equals(sommet2[1]) && sommet1[2]->equals(sommet2[2])) ||
				((sommet1[1]->equals(sommet2[2]) && sommet1[2]->equals(sommet2[1]))));

		}else if(sommet1[2]->getDist(sommet1[0]) == sommet2[2]->getDist(sommet2[0])){

			return ((sommet1[2]->equals(sommet2[2]) && sommet1[0]->equals(sommet2[0])) ||
				((sommet1[2]->equals(sommet2[0]) && sommet1[0]->equals(sommet2[2]))));

		}else{
			return false;
		}
	}
};
#endif