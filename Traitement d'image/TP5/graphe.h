#include <stdio.h>
#include <iostream>
#ifndef graphe_h
#define graphe_h

class Graphe{
private:
	int l1,l2,c1,c2,moyenne;
	Graphe* voisins[2];
public:
	Graphe(int l1, int c1, int l2, int c2,int moyenne);
	//Graphe(int l1,int c1, int l2,int c2,Graphe** voisins);
	void setVoisin(Graphe *v, int pos);
	void setVoisins(Graphe *v1, Graphe *v2);
	Graphe** getVoisins();
	int getMoyenne();
	int getL1();
	int getL2();
	int getC1();
	int getC2();
};
#endif