#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdio.h>
#include <iostream>
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

	Point** getPoints(){
		Point** pts = new Point*[3];
		pts[0]=new Point(sommets[0]->getX(),sommets[0]->getY(),sommets[0]->getZ());
		pts[1]=new Point(sommets[1]->getX(),sommets[1]->getY(),sommets[1]->getZ());
		pts[2]=new Point(sommets[2]->getX(),sommets[2]->getY(),sommets[2]->getZ());

		return pts;
	}

	int contains(Sommet* s1){
		int res = -1;
		for(int i=0;i<3;i++){
			if(this->getSommets()[i]->equals(s1)){
				return i;
			}
		}
		return res;
	}


	bool isVoisin(Triangle* tr){
		Sommet** sommet1 = this->getSommets();
		Sommet** sommet2 = tr->getSommets();
		if(((sommet1[0]->getDist(sommet1[1])-sommet2[0]->getDist(sommet2[1]))<=0.3) && ((sommet1[0]->getDist(sommet1[1])-sommet2[0]->getDist(sommet2[1]))>=-0.3)){
			
			return ((sommet1[0]->equals(sommet2[0]) && sommet1[1]->equals(sommet2[1])) ||
				((sommet1[0]->equals(sommet2[1]) && sommet1[1]->equals(sommet2[0]))));

		}else if(((sommet1[1]->getDist(sommet1[2])-sommet2[1]->getDist(sommet2[2]))<=0.3) && ((sommet1[1]->getDist(sommet1[2])-sommet2[1]->getDist(sommet2[2]))>=-0.3)){
			
			return ((sommet1[1]->equals(sommet2[1]) && sommet1[2]->equals(sommet2[2])) ||
				((sommet1[1]->equals(sommet2[2]) && sommet1[2]->equals(sommet2[1]))));

		}else if(((sommet1[2]->getDist(sommet1[0])-sommet2[2]->getDist(sommet2[0]))>=0.3) && ((sommet1[2]->getDist(sommet1[0])-sommet2[2]->getDist(sommet2[0]))<=-0.3)){
			
			return ((sommet1[2]->equals(sommet2[2]) && sommet1[0]->equals(sommet2[0])) ||
				((sommet1[2]->equals(sommet2[0]) && sommet1[0]->equals(sommet2[2]))));

		}else{
			return false;
		}
	}
};
#endif