#include "graphe.h"


Graphe::Graphe(int l1, int c1, int l2, int l3,int moyenne){
	l1=l1;
	c1=c1;
	l2=l2;
	c2=c2;
	moyenne =moyenne;
}

void Graphe::setVoisin(Graphe* v, int pos){
	voisins[pos] = v;
}

void Graphe::setVoisins(Graphe *v1, Graphe *v2){
	voisins[0]= v1;
	voisins[1]= v2;
}

Graphe** Graphe::getVoisins(){
	return voisins;
}

int Graphe::getMoyenne(){
	return moyenne;
}

int Graphe::getL1(){
	return l1;
}
 int Graphe::getL2(){
 	return l2;
 }

 int Graphe::getC1(){
 	return c1;
 }

 int Graphe::getC2(){
 	return c2;
 }
