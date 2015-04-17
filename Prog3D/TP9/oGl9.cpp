#include "oGl9.h"

using namespace std;

Triangle** tri;
int nbTri=0;


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
	//indi = indices;
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