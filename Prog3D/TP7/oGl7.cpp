#include "oGl7.h"

using namespace std;

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
 	glLineWidth(7);
 

 	// Triangles du "milieu"

 	glColor3f(0,0,1);
 	for(int i =1; i <(nbPara/2)-1;i++){
 		for(int j =0;j<nbMeridien-1;j++){
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
 		}
 	}
 	// ajouts les derniers triangles non ajouter
 	glBegin(GL_TRIANGLES);
 	for(int i =1;i<(nbPara/2)-1;i++){
 		glVertex3f(pts[nbMeridien-1][i]->getX(),pts[nbMeridien-1][i]->getY(),pts[nbMeridien-1][i]->getZ());
 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());

 		glVertex3f(pts[nbMeridien-1][i+1]->getX(),pts[nbMeridien-1][i+1]->getY(),pts[nbMeridien-1][i+1]->getZ());
 		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
 		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
 	}
 	glEnd();



 	// dessine les triangles aux extermité de la sphere
 	glBegin(GL_TRIANGLES);
 	for(int i = 0; i<nbMeridien-1;i++){
 		glVertex3f(pts[i][0]->getX(),pts[i][0]->getY(),pts[i][0]->getZ());
 		glVertex3f(pts[i][1]->getX(),pts[i][1]->getY(),pts[i][1]->getZ());
 		glVertex3f(pts[i+1][1]->getX(),pts[i+1][1]->getY(),pts[i+1][1]->getZ());
 	}
 	glEnd();
 	glBegin(GL_TRIANGLES);
 	glVertex3f(pts[0][0]->getX(),pts[0][0]->getY(),pts[0][0]->getZ());
 	glVertex3f(pts[0][1]->getX(),pts[0][1]->getY(),pts[0][1]->getZ());
 	glVertex3f(pts[nbMeridien-1][1]->getX(),pts[nbMeridien-1][1]->getY(),pts[nbMeridien-1][1]->getZ());
 	glEnd();

 	glBegin(GL_TRIANGLES);
 	for(int i =0;i<nbMeridien-1;i++){
 		glVertex3f(pts[i][(nbPara/2)]->getX(),pts[i][(nbPara/2)]->getY(),pts[i][(nbPara/2)]->getZ());
 		glVertex3f(pts[i][(nbPara/2)+1]->getX(),pts[i][(nbPara/2)+1]->getY(),pts[i][(nbPara/2)+1]->getZ());
 		glVertex3f(pts[i+1][(nbPara/2)+1]->getX(),pts[i+1][(nbPara/2)+1]->getY(),pts[i+1][(nbPara/2)+1]->getZ());
 	}
 	glEnd();
 	glBegin(GL_TRIANGLES);
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
 	glBegin(GL_TRIANGLES);
 	for(int i =0;i<nbPoints;i++){
		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i]->getX(),pts[1][i]->getY(),pts[1][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());

		glVertex3f(pts[0][i]->getX(),pts[0][i]->getY(),pts[0][i]->getZ());
		glVertex3f(pts[1][i+1]->getX(),pts[1][i+1]->getY(),pts[1][i+1]->getZ());
		glVertex3f(pts[0][i+1]->getX(),pts[0][i+1]->getY(),pts[0][i+1]->getZ());
 	}
	/*glVertex3f(pts[0]->getX(),pts[0]->getY(),pts[0]->getZ());
 	glVertex3f(pts[1]->getX(),pts[1]->getY(),pts[1]->getZ());

 	glVertex3f(pts[nbPoints-1]->getX(),pts[nbPoints-1]->getY(),pts[nbPoints-1]->getZ());
 	glVertex3f(pts[nbPoints-2]->getX(),pts[nbPoints-2]->getY(),pts[nbPoints-2]->getZ());*/

 	glEnd();
 	glColor3f(0,0,1);
 	glBegin(GL_POLYGON);
 	for(int i=0;i<nbPoints;i++){
 		glVertex3f(pts[0][i]->getX(), pts[0][i]->getY(),pts[0][i]->getZ());
 	}
 	glEnd();
 	glBegin(GL_POLYGON);
 	for(int i=0;i<nbPoints;i++){
 		glVertex3f(pts[1][i]->getX(), pts[1][i]->getY(), pts[1][i]->getZ());
 	}
 	glEnd();

 }