#include "oGl8.h"
#include "oGl7.h"

using namespace std;

Triangle** tri;// triangles composant le maillage
int nbTri; // nombre de triangle dans le maillage
int** indi;// indice des voisins de chaque triangle
int* trait;// stock les triangle traité (-1: non traité, 0 : couleur 1, 1 : couleur 2 ...)

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

void afficheSeg(int index, int color){
	//cout<<indi[2872][2]<<endl;
	bool isole;
	Point** tr1,**tr2;
	int r;// couleur du maillage (= segement)
	for(int i = 0; i<nbTri;i++){
		isole = true;
		//cout<<i<<" "<<endl;
		if(trait[i]==-1){// triangle non traité
			tr1 = tri[i]->getPoints();
			// Récupération des voisins
			for(int j =0;j<3;j++){
				//cout<<"la1"<<endl;
				if(indi[i][j]!=-1){
					tr2=tri[indi[i][j]]->getPoints();
					// si le voisin est déjà traité et appartient au même segement
					if(trait[indi[i][j]]!=-1 && getAngleDiedre(tr1,tr2)<=180 && getAngleDiedre(tr1,tr2)>=170){
						//cout<<"la2"<<endl;
						switch(trait[indi[i][j]]){
							case 0:
							r=0;
							glColor3f(1,0,0);
							break;
							case 1:
							r=1;
							glColor3f(0,1,0);
							break;
							case 2:
							r=2;
							glColor3f(0,0,1);
							break;
							default:
							glColor3f(0,0,0);
							break;
						}
						isole = false;

					}
				}
			}
			if(isole){// si le triangle n'a pas de voisin traité
				r = random() % 3;
				switch(r){// on lui affecte une couleur aléatoire
						case 0:
						glColor3f(1,0,0);
						break;
						case 1:
						glColor3f(0,1,0);
						break;
						case 2:
						glColor3f(0,0,1);
						break;
						default:
						glColor3f(0,0,0);
						break;
					}
			}
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
	  		trait[i]=r;
		}
		

	}
	/*cout<<"!!!!! "<<index<<endl;
	switch(color){
		case 0:
		glColor3f(1,0,0);
		break;
		case 1:
		glColor3f(0,1,0);
		break;
		case 2:
		glColor3f(0,0,1);
		break;
		default:
		glColor3f(0,0,0);
		break;
	}
	cout<<"x : "<<tri[index]->getSommets()[0]->getX()<<":"<<tri[index]->getSommets()[0]->getY()<<":"<<tri[index]->getSommets()[0]->getZ()<<endl;
	glBegin(GL_TRIANGLES);
  		glVertex3f(tri[index]->getSommets()[0]->getX(),
  			tri[index]->getSommets()[0]->getY(),
  			tri[index]->getSommets()[0]->getZ());

  		glVertex3f(tri[index]->getSommets()[1]->getX(),
  			tri[index]->getSommets()[1]->getY(),
  			tri[index]->getSommets()[1]->getZ());

  		glVertex3f(tri[index]->getSommets()[2]->getX(),
  			tri[index]->getSommets()[2]->getY(),
  			tri[index]->getSommets()[2]->getZ());
  	glEnd();

  	Point** tri1 = tri[index]->getPoints();
  	for(int i =0;i<3;i++){
  		//cout<<i<<"  "<<indi[index][i]<<"   "<<trait[indi[index][i]]<<endl;
  		if(indi[index][i]!=-1){// triangles voisins
  			if(trait[indi[index][i]]==0){// triangle non traité

  				Point** tri2 = tri[indi[index][i]]->getPoints();
  				double angle = getAngleDiedre(tri1,tri2);
  				trait[indi[index][i]]=1;
  				if(angle <=180 && angle >= 170 ){// meme segement
  					afficheSeg(indi[index][i],color);
  				}else{ // pas le meme segement
  					int col = rand() % 3;
  					while (col == color){
  						col = rand() % 3;
  					}
  					afficheSeg(indi[index][i],color);
  				}
  				

  			}
  			
  		}
  	}*/

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
		trait=new int[nbTri];
		for(int i =0;i<nbTri;i++){
			trait[i]=-1;
		}
	}else{
		cerr<<"erreur lors de la lectur du fichier"<<endl;
	}


}

/*
 * creer un tableau d'indice des triangles en enregistant
 * quelle triangle et voisin de quelle triangle
 */
int** getVoisins(){
	std::cout<<"taille : "<<nbTri<<std::endl;
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