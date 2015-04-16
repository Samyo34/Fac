#include "oGl8.h"

using namespace std;

Triangle** tri;
int nbTri;

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
	}else{
		cerr<<"erreur lors de la lectur du fichier"<<endl;
	}


}

/*
 * creer un tableau d'indice des triangles en enregistant
 * quelle triangle et voisin de quelle triangle
 */
int** getVoisins(){
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
	return indices;
}