#include "oGl.h"
#include "oGl3.h"
#include "figureGl.h"

Point** cylindre(Point* pointO, Point* pointD,long rayon, long hauteur, int nbMeridien){
	double x,y,z1,z2,angle;
	Point** cylindre = new Point*[nbMeridien*2];
	int cpt =0;
	for(int i = 0; i<nbMeridien;i++){
		angle = 2*M_PI*i/nbMeridien;
		x = rayon*cos(angle);
		y = rayon*sin(angle);
		z1 = -(hauteur/2);
		cylindre[cpt]=new Point(x,y,z1);
		cpt++;
		z2 = hauteur/2;
		cylindre[cpt]=new Point(x,y,z2);
		cpt++;
	}
	return cylindre;
}
/*
 *a est le centre du cercle (base), b le sommet du cone
 */
Point** cone(Point* a, Point* b, long rayon, long hauteur, int nbMeridien){
	double x,y,z,angle;
	Point** cone = new Point*[nbMeridien*2];
	int cpt=0;
	for(int i =0;i<nbMeridien;i++){
		angle = 2*M_PI*i/nbMeridien;
		cone[cpt]=b;
		cpt++;
		x = rayon*cos(angle);
		y = rayon*sin(angle);
		z=hauteur; // ?
		cone[cpt]= new Point(x,y,z);
		cpt++;
	}
	return cone;
}


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
			pts[i][j]=new Point(x,y,z);
		}
		//pts[i][nbPara+1]=sud;
	}
	return pts;
}

void drawSphere(Point*** pts,int nbMeridien,int nbPara){
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glPointSize(5);
    glBegin(GL_POLYGON);
	for(int i=0;i<nbMeridien-1;i++){
		for(int j=0;j<nbPara-1;j++){

			glBegin(GL_LINES);
			glVertex3f(
				pts[i][j]->getX(),
				pts[i][j]->getY(),
				pts[i][j]->getZ());
			glVertex3f(
				pts[i+1][j]->getX(),
				pts[i+1][j]->getY(),
				pts[i+1][j]->getZ());
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(pts[i+1][j]->getX(), pts[i+1][j]->getY(), pts[i+1][j]->getZ());
			glVertex3f(pts[i+1][j+1]->getX(), pts[i+1][j+1]->getY(), pts[i+1][j+1]->getZ());
			glEnd();
		}
	}

	glBegin(GL_LINES);
	glVertex3f(pts[0][1]->getX(), pts[0][1]->getY(), pts[0][1]->getZ());
	glVertex3f(pts[nbMeridien - 1][1]->getX(), pts[nbMeridien-1][1]->getY(), pts[nbMeridien-1][1]->getZ());
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	for(int i=0;i<nbMeridien-1;i++){
		for(int j=0;j<nbPara;j++){


			glVertex3f(
				pts[i][j]->getX(),
				pts[i][j]->getY(),
				pts[i][j]->getZ());
			glVertex3f(
				pts[i+1][j]->getX(),
				pts[i+1][j]->getY(),
				pts[i+1][j]->getZ());
		}
	}
	glEnd();
}

void drawCone(Point** pts, long nbPoints){
	Point** temp = new Point*[nbPoints/2];
	int cpt=0;
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glPointSize(5);
    glBegin(GL_QUADS);
	for(int i =2;i<nbPoints;i+=2){
		//std::cout<<pts[i]->getX()<<" "<<pts[i]->getY()<<" "<<pts[i]->getZ()<<std::endl;
		glVertex3f(pts[i-2]->getX(), pts[i-2]->getY(), pts[i-2]->getZ());
		glVertex3f(pts[i-1]->getX(), pts[i-1]->getY(), pts[i-1]->getZ());
		glVertex3f(pts[i+1]->getX(), pts[i+1]->getY(), pts[i+1]->getZ());
		glVertex3f(pts[i]->getX(), pts[i]->getY(), pts[i]->getZ());
		temp[cpt]=pts[i-1];
		cpt++;
		
	}
	glVertex3f(pts[0]->getX(),pts[0]->getY(),pts[0]->getZ());
	glVertex3f(pts[1]->getX(),pts[1]->getY(),pts[1]->getZ());

	glVertex3f(pts[nbPoints-1]->getX(),pts[nbPoints-1]->getY(),pts[nbPoints-1]->getZ());
	glVertex3f(pts[nbPoints-2]->getX(),pts[nbPoints-2]->getY(),pts[nbPoints-2]->getZ());

	glEnd();
	temp[cpt]=pts[nbPoints-1];
	cpt++;
	temp[cpt]=pts[1];
	cpt++;
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	for(int i =0;i<cpt;i++){
		glVertex3f(temp[i]->getX(),temp[i]->getY(),temp[i]->getZ());
	}
	glEnd();


}

void drawCylindre(Point** pts, long nbPoints){
	Point** pts1 = new Point*[nbPoints];
	Point** pts2 = new Point*[nbPoints];
	int cpt=0;

	glColor3f(1, 0, 0);
	glLineWidth(2);
    glBegin(GL_QUADS);
	for(int i =2;i<nbPoints;i+=2){
		//std::cout<<i<<" "<<pts[i]->getX()<<" "<<pts[i]->getY()<<" "<<pts[i]->getY()<<std::endl;
		glVertex3f(pts[i-2]->getX(), pts[i-2]->getY(), pts[i-2]->getZ());
		pts1[cpt]=pts[i-2];
		glVertex3f(pts[i-1]->getX(), pts[i-1]->getY(), pts[i-1]->getZ());
		pts2[cpt]=pts[i-1];
		cpt++;
		glVertex3f(pts[i+1]->getX(), pts[i+1]->getY(), pts[i+1]->getZ());
		pts2[cpt]=pts[i+1];
		glVertex3f(pts[i]->getX(), pts[i]->getY(), pts[i]->getZ());
		pts1[cpt]=pts[i];
		cpt++;
	}
	glVertex3f(pts[0]->getX(),pts[0]->getY(),pts[0]->getZ());
	glVertex3f(pts[1]->getX(),pts[1]->getY(),pts[1]->getZ());

	glVertex3f(pts[nbPoints-1]->getX(),pts[nbPoints-1]->getY(),pts[nbPoints-1]->getZ());
	glVertex3f(pts[nbPoints-2]->getX(),pts[nbPoints-2]->getY(),pts[nbPoints-2]->getZ());
	

	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	for(int i=0;i<cpt;i++){
		glVertex3f(pts1[i]->getX(), pts1[i]->getY(), pts1[i]->getZ());
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(int i=0;i<cpt;i++){
		glVertex3f(pts2[i]->getX(), pts2[i]->getY(), pts2[i]->getZ());
	}
	glEnd();
	
}