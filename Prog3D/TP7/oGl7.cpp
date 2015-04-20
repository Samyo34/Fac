#include "oGl7.h"

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


/*
 * retourne les points constituant la sphere de centre "centre"
 * de rayon "rayon" avec nbMeridien méridien et nbPara parallèle
 */
Point*** sphere(Point* centre, long rayon, int nbMeridien, int nbPara){
 	Point*** pts = new Point**[nbMeridien];
 	Point* nord = new Point(0,0,rayon);
 	Point* sud = new Point(0,0,-rayon);
 	double x,y,z;

 	double angleMeri, anglePara;
 	for(int i =0;i<nbMeridien;i++){
 		angleMeri=2*M_PI*i/nbMeridien;
 		pts[i]=new Point*[nbPara];
		//pts[i][0]=nord;
 		for(int j=0;j<nbPara;j++){
 			anglePara = 2*M_PI*j/nbPara;
 			x = rayon*sin(anglePara)*cos(angleMeri);
 			y = rayon* sin(anglePara)*sin(angleMeri);
 			z = rayon * cos(anglePara);
 			pts[i][j]=new Point(centre->getX()+x,centre->getY()+y,centre->getZ()+z);
 		}
		//pts[i][nbPara+1]=sud;
 	}
 	return pts;
 }

/*
 * Affiche la sphere définie par les points contenu dans pts
 */
void drawSphere(Point*** pts,int nbMeridien,int nbPara){
 	glColor3f(0, 1, 0);
 	glLineWidth(4);
 

 	// Triangles du "milieu"

 	glColor3f(0,0,1);
 	for(int i =1; i <(nbPara/2)-1;i++){
 		for(int j =0;j<nbMeridien-1;j++){
 			glColor3f(0, 1, 0);
 			glBegin(GL_TRIANGLES);
 			glVertex3f(pts[j][i]->getX(),pts[j][i]->getY(),pts[j][i]->getZ());
 			glVertex3f(pts[j][i+1]->getX(),pts[j][i+1]->getY(),pts[j][i+1]->getZ());
 			glVertex3f(pts[j+1][i]->getX(),pts[j+1][i]->getY(),pts[j+1][i]->getZ());
 			glEnd();
 			glBegin(GL_TRIANGLES);
 			glVertex3f(pts[j][i+1]->getX(),pts[j][i+1]->getY(),pts[j][i+1]->getZ());
 			glVertex3f(pts[j+1][i+1]->getX(),pts[j+1][i+1]->getY(),pts[j+1][i+1]->getZ());
 			glVertex3f(pts[j+1][i]->getX(),pts[j+1][i]->getY(),pts[j+1][i]->getZ());
 			glEnd();

 			glColor3f(1,0,0);
 			glBegin(GL_LINES);
 			glVertex3f(pts[j][i]->getX(),pts[j][i]->getY(),pts[j][i]->getZ());
 			glVertex3f(pts[j][i+1]->getX(),pts[j][i+1]->getY(),pts[j][i+1]->getZ());
 			glVertex3f(pts[j+1][i]->getX(),pts[j+1][i]->getY(),pts[j+1][i]->getZ());
 			glEnd();
 			glBegin(GL_LINES);
 			glVertex3f(pts[j][i+1]->getX(),pts[j][i+1]->getY(),pts[j][i+1]->getZ());
 			glVertex3f(pts[j+1][i+1]->getX(),pts[j+1][i+1]->getY(),pts[j+1][i+1]->getZ());
 			glVertex3f(pts[j+1][i]->getX(),pts[j+1][i]->getY(),pts[j+1][i]->getZ());
 			glEnd();
 			glColor3f(0, 1, 0);
 		}
 	}
 	// ajouts les derniers triangles non ajouter
 	
 	for(int i =1;i<(nbPara/2)-1;i++){
 		glColor3f(0, 1, 0);
 		glBegin(GL_TRIANGLES);
 		glVertex3f(pts[nbMeridien-1][i]->getX(),pts[nbMeridien-1][i]->getY(),pts[nbMeridien-1][i]->getZ());
 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());

 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
 		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
 		glEnd();
 		glColor3f(1,0,0);
 		glBegin(GL_LINES);
 		glVertex3f(pts[nbMeridien-1][i]->getX(),pts[nbMeridien-1][i]->getY(),pts[nbMeridien-1][i]->getZ());
 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());

 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
 		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
 		glEnd();
 		glColor3f(0, 1, 0);
 	}
 	



 	// dessine les triangles aux extermité de la sphere
 	
 	for(int i = 0; i<nbMeridien-1;i++){
 		glColor3f(0,1,0);
 		glBegin(GL_TRIANGLES);
 		glVertex3f(pts[i][0]->getX(),pts[i][0]->getY(),pts[i][0]->getZ());
 		glVertex3f(pts[i][1]->getX(),pts[i][1]->getY(),pts[i][1]->getZ());
 		glVertex3f(pts[i+1][1]->getX(),pts[i+1][1]->getY(),pts[i+1][1]->getZ());
 		glEnd();
 		glColor3f(1,0,0);
 		glBegin(GL_LINES);
 		glVertex3f(pts[i][0]->getX(),pts[i][0]->getY(),pts[i][0]->getZ());
 		glVertex3f(pts[i][1]->getX(),pts[i][1]->getY(),pts[i][1]->getZ());
 		glVertex3f(pts[i+1][1]->getX(),pts[i+1][1]->getY(),pts[i+1][1]->getZ());
 		glEnd();
 		glColor3f(0,1,0);

 	}
 	
 	glBegin(GL_TRIANGLES);
 	glVertex3f(pts[0][0]->getX(),pts[0][0]->getY(),pts[0][0]->getZ());
 	glVertex3f(pts[0][1]->getX(),pts[0][1]->getY(),pts[0][1]->getZ());
 	glVertex3f(pts[nbMeridien-1][1]->getX(),pts[nbMeridien-1][1]->getY(),pts[nbMeridien-1][1]->getZ());
 	glEnd();

 	glColor3f(1,0,0);
 	glBegin(GL_LINES);
 	glVertex3f(pts[0][0]->getX(),pts[0][0]->getY(),pts[0][0]->getZ());
 	glVertex3f(pts[0][1]->getX(),pts[0][1]->getY(),pts[0][1]->getZ());
 	glVertex3f(pts[nbMeridien-1][1]->getX(),pts[nbMeridien-1][1]->getY(),pts[nbMeridien-1][1]->getZ());
 	glEnd();
 	glColor3f(0,1,0);

 	
 	for(int i =0;i<nbMeridien-1;i++){
 		glColor3f(0,1,0);
 		glBegin(GL_TRIANGLES);
 		glVertex3f(pts[i][(nbPara/2)]->getX(),pts[i][(nbPara/2)]->getY(),pts[i][(nbPara/2)]->getZ());
 		glVertex3f(pts[i][(nbPara/2)+1]->getX(),pts[i][(nbPara/2)+1]->getY(),pts[i][(nbPara/2)+1]->getZ());
 		glVertex3f(pts[i+1][(nbPara/2)+1]->getX(),pts[i+1][(nbPara/2)+1]->getY(),pts[i+1][(nbPara/2)+1]->getZ());
 		glEnd();
 		glColor3f(1,0,0);
 		glBegin(GL_LINES);
 		glVertex3f(pts[i][(nbPara/2)]->getX(),pts[i][(nbPara/2)]->getY(),pts[i][(nbPara/2)]->getZ());
 		glVertex3f(pts[i][(nbPara/2)+1]->getX(),pts[i][(nbPara/2)+1]->getY(),pts[i][(nbPara/2)+1]->getZ());
 		glVertex3f(pts[i+1][(nbPara/2)+1]->getX(),pts[i+1][(nbPara/2)+1]->getY(),pts[i+1][(nbPara/2)+1]->getZ());
 		glEnd();
 		glColor3f(0,1,0);
 	}
 	glColor3f(0,1,0);
 	glBegin(GL_TRIANGLES);
 	glVertex3f(pts[0][(nbPara/2)]->getX(),pts[0][(nbPara/2)]->getY(),pts[0][(nbPara/2)]->getZ());
 	glVertex3f(pts[0][(nbPara/2)+1]->getX(),pts[0][(nbPara/2)+1]->getY(),pts[0][(nbPara/2)+1]->getZ());
 	glVertex3f(pts[nbMeridien-1][(nbPara/2)+1]->getX(),pts[nbMeridien-1][(nbPara/2)+1]->getY(),pts[nbMeridien-1][(nbPara/2)+1]->getZ());
 	glEnd();
 	glColor3f(1,0,0);
 	glBegin(GL_LINES);
 	glVertex3f(pts[0][(nbPara/2)]->getX(),pts[0][(nbPara/2)]->getY(),pts[0][(nbPara/2)]->getZ());
 	glVertex3f(pts[0][(nbPara/2)+1]->getX(),pts[0][(nbPara/2)+1]->getY(),pts[0][(nbPara/2)+1]->getZ());
 	glVertex3f(pts[nbMeridien-1][(nbPara/2)+1]->getX(),pts[nbMeridien-1][(nbPara/2)+1]->getY(),pts[nbMeridien-1][(nbPara/2)+1]->getZ());
 	glEnd();
 	
}

 Point*** cylindre(Point* pointO,long rayon, long hauteur, int nbMeridien){
	Point*** p = new Point**[2];
	p[0] = new Point*[nbMeridien+1];
	for (int i = 0; i < nbMeridien+1; ++i) {
		double angle = (2 * M_PI * i) / nbMeridien;
		p[0][i] = new Point(pointO->getX() + rayon*cos(angle), pointO->getY() + rayon*sin(angle), pointO->getZ());
	}
	p[1] = new Point*[nbMeridien+1];
	for (int i = 0; i < nbMeridien+1; ++i) {
		p[1][i] = new Point(p[0][i]->getX(), p[0][i]->getY(), p[0][i]->getZ() + hauteur);
	}
	return p;
 }


 void drawCylindre(Point*** pts, long nbPoints){
 	Point** pts1 = new Point*[nbPoints];
 	Point** pts2 = new Point*[nbPoints];
 	glColor3f(1, 0, 0);
 	glLineWidth(2);
 	
 	for(int i =0;i<nbPoints;i++){
 		glColor3f(1, 0, 0);
 		glBegin(GL_TRIANGLES);
		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i]->getX(),pts[1][i]->getY(),pts[1][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());

		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());
		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
		glEnd();
	glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i]->getX(),pts[1][i]->getY(),pts[1][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());

		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());
		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
		glEnd();
		glColor3f(1, 0, 0);
 	}
	/*glVertex3f(pts[0]->getX(),pts[0]->getY(),pts[0]->getZ());
 	glVertex3f(pts[1]->getX(),pts[1]->getY(),pts[1]->getZ());

 	glVertex3f(pts[nbPoints-1]->getX(),pts[nbPoints-1]->getY(),pts[nbPoints-1]->getZ());
 	glVertex3f(pts[nbPoints-2]->getX(),pts[nbPoints-2]->getY(),pts[nbPoints-2]->getZ());*/

 	glBegin(GL_POLYGON);
 	for(int i=0;i<nbPoints;i++){
 		
 		glVertex3f(pts[0][i]->getX(), pts[0][i]->getY(),pts[0][i]->getZ());
 		
 	}
 	glEnd();
 	
 	glBegin(GL_POLYGON);
 	for(int i=0;i<nbPoints;i++){
 		
 		glVertex3f(pts[1][nbPoints-i]->getX(), pts[1][nbPoints-i]->getY(), pts[1][nbPoints-i]->getZ());
 		
 	}
 	glEnd();
 	

 }

 void areteVive(double seuil){
 	glBegin(GL_LINES);
 	for(int i=0;i<nbTri-1;i++){
 		if(getAngleDiedre(tri[i],tri[i+1])<seuil){
 			for(int j =0;j<3;j++){
 				for(int k=0;k<3;k++){
 					if(tri[i]->getSommets()[j]->equals(tri[i+1]->getSommets()[k])){
 						glVertex3f(tri[i]->getSommets()[j]->getX(),tri[i]->getSommets()[j]->getY(),tri[i]->getSommets()[j]->getZ());
 					}
 				}
 			}
 			
 		}
 	}
 	glEnd();
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
 * Calcul l'angle diedre entre triangle1 et triangle2
 * on suppose que les triangles sont reprsenter par 3 points
 * et que l'on lit les points dans le même sence
 */
 double getAngleDiedre(Triangle* triangle1, Triangle* triangle2){
 	Vector v1(triangle1->getSommets()[1]->getX()-triangle1->getSommets()[0]->getX(),
 			triangle1->getSommets()[1]->getY()-triangle1->getSommets()[0]->getY(),
 			triangle1->getSommets()[1]->getZ()-triangle1->getSommets()[0]->getZ());

 	Vector v2(triangle1->getSommets()[2]->getX()-triangle1->getSommets()[0]->getX(),
 			triangle1->getSommets()[2]->getY()-triangle1->getSommets()[0]->getY(),
 			triangle1->getSommets()[2]->getZ()-triangle1->getSommets()[0]->getZ());
 	Vector* vec1 = v1.vectoriel(v2);// vecteur normal du triangle1
 	vec1->normalize();

 	Vector v3(triangle2->getSommets()[1]->getX()-triangle2->getSommets()[0]->getX(),
 			triangle2->getSommets()[1]->getY()-triangle2->getSommets()[0]->getY(),
 			triangle2->getSommets()[1]->getZ()-triangle2->getSommets()[0]->getZ());

 	Vector v4(triangle2->getSommets()[2]->getX()-triangle2->getSommets()[0]->getX(),
 			triangle2->getSommets()[2]->getY()-triangle2->getSommets()[0]->getY(),
 			triangle2->getSommets()[2]->getZ()-triangle2->getSommets()[0]->getZ());

 	Vector* vec2 = v3.vectoriel(v4);
 	vec2->normalize(); // vecteur normal du triangle2

 	return vec1->angle(*vec2)*(180/PI);

 }