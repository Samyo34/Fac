#include "oGl9.h"

using namespace std;

Triangle** tri;
int nbTri;
int** indi;// indice des voisins de chaque triangle


/*
 * Retourne un tableau d'entier represantant
 * les valeurs écrite dans une ligne
 */
double* getVal(vector<string> ligne){
	double* tab= new double[4];
	for(int i =0;i<ligne.size();i++){
		tab[i]=atof(ligne[i].c_str());
	}
	return tab;
}

vector<string> split(string ligne){
	istringstream iss(ligne);
	vector<string> res;
	string mot;
	while(getline(iss,mot,' ')){
		res.push_back(mot);
	}
	return res;
}


Point** makeCube(){
	ofstream fichier("cube.off", ios::out | ios::trunc);
	if(fichier){
		fichier << "OFF"<<endl;
		fichier << "8 12"<<endl;
		fichier << "-5 -5 5"<<endl;//0
		fichier << "5 -5 5"<<endl;//1
		fichier << "-5 5 5"<<endl;//2
		fichier << "5 5 5"<<endl;//3
		fichier << "-5 5 -5"<<endl;//4
		fichier << "5 5 -5"<<endl;//5
		fichier << "-5 -5 -5"<<endl;//6
		fichier << "5 -5 -5"<<endl;//7
		fichier << "3 0 2 3"<<endl;
		fichier << "3 0 3 1"<<endl;
		fichier << "3 6 4 2"<<endl;
		fichier << "3 6 2 0"<<endl;
		fichier << "3 7 5 4"<<endl;
		fichier << "3 7 4 6"<<endl;
		fichier << "3 1 3 5"<<endl;
		fichier << "3 1 5 7"<<endl;
		fichier << "3 6 0 1"<<endl;
		fichier << "3 6 1 7"<<endl;
		fichier << "3 2 4 5"<<endl;
		fichier << "3 2 5 3"<<endl; 

		fichier.close();

	}else{
		cerr<< "Erreur à l'ouverture du fichier"<<endl;
	}

}

void affiche(){
	glColor3f(0,1,0);
	for(int i =0;i<nbTri;i++){
		glBegin(GL_TRIANGLES);
  		glVertex3f(tri[i]->getSommets()[0]->getX(),
  			tri[i]->getSommets()[0]->getY(),
  			tri[i]->getSommets()[0]->getZ());

  		glVertex3f(tri[i]->getSommets()[1]->getX(),
  			tri[i]->getSommets()[1]->getY(),
  			tri[i]->getSommets()[1]->getZ());

  		glVertex3f(tri[i]->getSommets()[2]->getX(),
  			tri[i]->getSommets()[2]->getY(),
  			tri[i]->getSommets()[2]->getZ());
  		glEnd();
	}
	glColor3f(1,0,0);
	for(int i =0;i<nbTri;i++){
		glBegin(GL_LINE_STRIP);
		glVertex3f(tri[i]->getSommets()[0]->getX(),
  			tri[i]->getSommets()[0]->getY(),
  			tri[i]->getSommets()[0]->getZ());

  		glVertex3f(tri[i]->getSommets()[1]->getX(),
  			tri[i]->getSommets()[1]->getY(),
  			tri[i]->getSommets()[1]->getZ());

  		glVertex3f(tri[i]->getSommets()[2]->getX(),
  			tri[i]->getSommets()[2]->getY(),
  			tri[i]->getSommets()[2]->getZ());

  		glVertex3f(tri[i]->getSommets()[0]->getX(),
  			tri[i]->getSommets()[0]->getY(),
  			tri[i]->getSommets()[0]->getZ());

  		glEnd();
	}
	

}

void readFile(char* fileName){
	int nbSommet, nbTriangles;
	ifstream fichier(fileName, ios::in);
	string ligne;
	

	if(fichier){

		getline(fichier,ligne);// Lecture OFF
		getline(fichier,ligne);// nombre de sommet, triangles...
		double* vals = getVal(split(ligne));
		nbSommet = (int)vals[0];
		nbTriangles = (int)vals[1];
		Sommet *sommets[nbSommet];
		Triangle *triangles[nbTriangles];
		tri = new Triangle*[nbTriangles];

		// Lecture Sommets
		for(int i = 0;i<nbSommet;i++){
			getline(fichier, ligne);
			vals = getVal(split(ligne));
			sommets[i]= new Sommet(vals[0],vals[1],vals[2]);
		}

		// Lecture triangles
		for(int i=0;i<nbTriangles;i++){
			getline(fichier,ligne);
			vals = getVal(split(ligne));
			tri[i]=new Triangle(new Sommet(sommets[(int)vals[1]]),
									new Sommet(sommets[(int)vals[2]]),
									new Sommet(sommets[(int)vals[3]]));
		}
		nbTri = nbTriangles;
		/*trait=new int[nbTri];
		for(int i =0;i<nbTri;i++){
			trait[i]=-1;
		}*/
	}else{
		cerr<<"erreur lors de la lectur du fichier"<<endl;
	}


}

/*
 * creer un tableau d'indice des triangles en enregistant
 * quelle triangle et voisin de quelle triangle
 */
int** getVoisins(){
	//std::cout<<"taille : "<<nbTri<<std::endl;
	int** indices = new int*[nbTri];
	for(int i =0; i< nbTri; i++){
		indices[i]=new int[3];
		indices[i][0]=-1;indices[i][1]=-1;indices[i][2]=-1;
		for(int j = 0;j<nbTri;j++){
			if(i != j){

				if(tri[i]->isVoisin(tri[j])){

					if(indices[i][0]!=-1){
						if(indices[i][1]!=-1){
							indices[i][2]=j;
						}else{
							indices[i][1]=j;
						}
					}else{
						indices[i][0]=j;
					}
				}

			}	
		}
	}
	indi = indices;
	return indices;
}

/*
 * modifie "tri" pour avoir la meme figure avec
 * les points p1 et p2 fusionné
 * (p1 et p2 sont identifiés par leurs coordonnées) 
 */
void fusion(Point* p1,Point* p2){
	double x,y,z;
	x = (p1->getX()+p2->getX())/2;
	y = (p1->getY()+p2->getY())/2;
	z = (p1->getZ()+p2->getZ())/2;
	Sommet* fu = new Sommet(x,y,z);

	Sommet* s1 = new Sommet(p1);
	Sommet* s2 = new Sommet(p2);

	int res1,res2;

	for(int i =0;i<nbTri;i++){
		res1 = tri[i]->contains(s1);
		res2 = tri[i]->contains(s2);
		if(res1 != -1){
			tri[i]->getSommets()[res1]=fu;
		}
		if(res2 != -1){
			tri[i]->getSommets()[res2]=fu;
		}
	}
}


/*
 * modifie tri pour obtenir un maillage plus fin
 */
void raffineAll(){
	Triangle** triangles = new Triangle*[nbTri*4];
	Triangle** temp = new Triangle*[4];
	int cpt=0;
	for(int i=0;i<nbTri;i++){
		temp = raffinement(tri[i]);
		for(int j=0;j<4;j++){
			triangles[cpt]=temp[j];
			cpt++;
		}
	}
	tri = triangles;
	nbTri = nbTri*4;
}

/*
 * Raffine le triangle passé en parametre
 * retourne 4 triangle correspondant au triangle raffiné
 */
Triangle** raffinement(Triangle* triangle){
	Triangle** tr = new Triangle*[4];
	double x,y,z;
	x=(triangle->getSommets()[0]->getX()+triangle->getSommets()[1]->getX())/2;
	y=(triangle->getSommets()[0]->getY()+triangle->getSommets()[1]->getY())/2;
	z=(triangle->getSommets()[0]->getZ()+triangle->getSommets()[1]->getZ())/2;
	Sommet* s1 = new Sommet(x,y,z);

	x=(triangle->getSommets()[1]->getX()+triangle->getSommets()[2]->getX())/2;
	y=(triangle->getSommets()[1]->getY()+triangle->getSommets()[2]->getY())/2;
	z=(triangle->getSommets()[1]->getZ()+triangle->getSommets()[2]->getZ())/2;
	Sommet* s2 = new Sommet(x,y,z);

	x=(triangle->getSommets()[0]->getX()+triangle->getSommets()[2]->getX())/2;
	y=(triangle->getSommets()[0]->getY()+triangle->getSommets()[2]->getY())/2;
	z=(triangle->getSommets()[0]->getZ()+triangle->getSommets()[2]->getZ())/2;
	Sommet* s3 = new Sommet(x,y,z);

	tr[0]=new Triangle(triangle->getSommets()[0],s1,s3);
	tr[1]=new Triangle(s1,triangle->getSommets()[1],s2);
	tr[2]=new Triangle(s3,s2,triangle->getSommets()[2]);
	tr[3]=new Triangle(s1,s2,s3);

	return tr;

}

/*
 * Modifie tri en réalisant une subdivision butterfly
 */
void butterflyFull(double niv){
	Triangle** triangles = new Triangle*[nbTri*4];
	Sommet* s1,*s2,*s3;
	int cpt=0;
	for(int i = 0;i<nbTri;i++){
		if(isMilieu(i)){
			cout<<i<<"pouet1"<<endl;
			s1 = butterfly(tri[i],0,1,i,niv);
			s2 = butterfly(tri[i],1,2,i,niv);
			s3 = butterfly(tri[i],0,2,i,niv);
			cout<<i<<"pouet2"<<endl;
			triangles[cpt]= new Triangle(tri[i]->getSommets()[0],s1,s3);
			cpt++;
			triangles[cpt]= new Triangle(s1,tri[i]->getSommets()[1],s2);
			cpt++;
			triangles[cpt]= new Triangle(s3,s2,tri[i]->getSommets()[2]);
			cpt++;
			triangles[cpt]= new Triangle(s1,s2,s3);
		}else{
			triangles[cpt]=tri[i];
			cpt++;
		}
	}
	cout<<"pouet"<<endl;
	Triangle** t = new Triangle*[cpt];
	for(int i=0;i<cpt;i++){
		t[i]=triangles[i];
	}
	tri = t;
	nbTri = cpt;
}
/*
 * retourne vrai si le triangle d'indice pos est au milieu de trois autres triangles
 */
bool isMilieu(int pos){
	bool res = true;
		for(int i=0;i<3;i++){
			if(indi[pos][i]==-1){
				return false;
			}
		}
		return res;
}

/*
 * construit le nouveau sommet de l'arete a1a2 passé en paramètre
 * la numérotation des sommets provient de : http://www.dmi.usherb.ca/~egli/butter12.pdf (p2)
 * retourne le nouveau sommet créé
 */ 
Sommet* butterfly(Triangle* t,int a1, int a2, int indiceTri, double niv){
	Triangle** triangles = new Triangle*[4];
	// récupération des 8 sommets interessant
	Sommet* p1 = t->getSommets()[a1];
	Sommet* p2 = t->getSommets()[a2];
	Sommet* p3;
	if(a1 == 0 && a2 == 1 || a1 == 1 && a2 == 0){
		p3 = t->getSommets()[2];
	}else if((a1 == 1 && a2 == 2) || (a1 == 2 && a2 == 1)){
		p3 = t->getSommets()[0];
	}else{
		p3 = t->getSommets()[1];
	}
	
	Sommet* p4, *p5,*p6,*p7,*p8;
	int res1,res2;
	for(int i=0;i<3;i++){
		if(indi[indiceTri][i]!=-1){
			// p5
			res1 = tri[indi[indiceTri][i]]->contains(p1);
			res2 = tri[indi[indiceTri][i]]->contains(p3);
			if(res1 != -1 && res2 != -1){
				if((res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 0)){
					p5 = tri[indi[indiceTri][i]]->getSommets()[2];
				}else if((res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)){
					p5 = tri[indi[indiceTri][i]]->getSommets()[0];
				}else{
					p5 = tri[indi[indiceTri][i]]->getSommets()[1];
				}
			}
			// p7
			res1 = tri[indi[indiceTri][i]]->contains(p2);
			res2 = tri[indi[indiceTri][i]]->contains(p3);
			if(res1 != -1 && res2 != -1){
				if((res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 0)){
					p7 = tri[indi[indiceTri][i]]->getSommets()[2];
				}else if((res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)){
					p7 = tri[indi[indiceTri][i]]->getSommets()[0];
				}else{
					p7 = tri[indi[indiceTri][i]]->getSommets()[1];
				}
			}
			//p4->p6,p8
			res1 = tri[indi[indiceTri][i]]->contains(p1);
			res2 = tri[indi[indiceTri][i]]->contains(p2);
			if(res1 != -1 && res2 != -1){//p4
				if((res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 0)){
					p4 = tri[indi[indiceTri][i]]->getSommets()[2];
				}else if((res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)){
					p4 = tri[indi[indiceTri][i]]->getSommets()[0];
				}else{
					p4 = tri[indi[indiceTri][i]]->getSommets()[1];
				}
				//p8
				int pos = indi[indiceTri][i];
				for(int j=0;j<3;j++){
					res1 = tri[indi[pos][j]]->contains(p2);
					res2 = tri[indi[pos][j]]->contains(p4);
					if(res1 != -1 && res2 != -1){
						if((res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 0)){
							p8 = tri[indi[indiceTri][i]]->getSommets()[2];
						}else if((res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)){
							p8 = tri[indi[indiceTri][i]]->getSommets()[0];
						}else{
							p8 = tri[indi[indiceTri][i]]->getSommets()[1];
						}

					}
					//p6
					res1 = tri[indi[pos][j]]->contains(p1);
					res2 = tri[indi[pos][j]]->contains(p4);
					if(res1 != -1 && res2 != -1){
						if((res1 == 0 && res2 == 1) || (res1 == 1 && res2 == 0)){
							p6 = tri[indi[indiceTri][i]]->getSommets()[2];
						}else if((res1 == 1 && res2 == 2) || (res1 == 2 && res2 == 1)){
							p6 = tri[indi[indiceTri][i]]->getSommets()[0];
						}else{
							p6 = tri[indi[indiceTri][i]]->getSommets()[1];
						}
					}
				}
			}

				
			}
		}		
	// Construction des nouveaux sommets
	double x,y,z;
	x = (((p1->getX()+p2->getX())/2)+
		(2*niv*(p3->getX()+p4->getX()))-
		(niv*(p5->getX()+p6->getX()+p7->getX())));

	y = (((p1->getY()+p2->getY())/2)+
		(2*niv*(p3->getY()+p4->getY()))-
		(niv*(p5->getY()+p6->getY()+p7->getY())));

	z = (((p1->getZ()+p2->getZ())/2)+
		(2*niv*(p3->getZ()+p4->getZ()))-
		(niv*(p5->getZ()+p6->getZ()+p7->getZ())));

	return new Sommet(x,y,z);
}