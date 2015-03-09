#include "oGl3.h"


Point** surf_cyle(Point ** tabPointOfCurve, long nbPointsCourbe, Point ** ab, long nbPointDroite){
	
	float v,u;
	Point** pts = new Point*[nbPointsCourbe*nbPointDroite];
	int pos=0;
	for(int i =0; i<nbPointsCourbe;i++){// parccours des points de la courbe
		u = 1 /(float)nbPointsCourbe * (float)i;
		for(int j =0;j<nbPointDroite;j++){//parcours des points de la droite
			v=1/(float)nbPointDroite * (float)j;
			double x = tabPointOfCurve[i]->getX() + ab[j]->getX();
			double y = tabPointOfCurve[i]->getY() + ab[j]->getY();
			double z = tabPointOfCurve[i]->getZ() + ab[j]->getZ();
			//std::cout<<x<<" "<<y<<" "<<z<<std::endl;
			pts[pos]= new Point(x,y,z);
			pos++;
		}

	}

	return pts;
}


void drawSurf(Point** tabPointOfCurve, long nbPoint){
	glLineWidth(4);
    glBegin(GL_TRIANGLE_STRIP);
    	std::cout<<tabPointOfCurve[0]->getX()<<std::endl;
    	glVertex3f(tabPointOfCurve[0]->getX(),tabPointOfCurve[0]->getY(),tabPointOfCurve[0]->getZ());
       	glVertex3f(tabPointOfCurve[1]->getX(),tabPointOfCurve[1]->getY(),tabPointOfCurve[1]->getZ());
       	glVertex3f(tabPointOfCurve[2]->getX(),tabPointOfCurve[2]->getY(),tabPointOfCurve[2]->getZ());
       /* for(int i = 0; i < nbPoint;i++){
        	glVertex3f(tabPointOfCurve[i]->getX(),tabPointOfCurve[i]->getY(),tabPointOfCurve[i]->getZ());
        }*/
    glEnd();
}

Point*** surfaceReglee(Point** controlPointU,long nbCtrlPointU, Point** controlPointV,long nbCtrlPointV){
	Point** curvU = BezierCurveByCasteljau(controlPointU,nbCtrlPointU,50);
	Point** curvV = BezierCurveByCasteljau(controlPointV,nbCtrlPointV,50);

	Point*** surf = new Point**[50];

	for(int i =0;i<50;i++){
			Point** pts = new Point*[2];
			pts[0]= curvU[i];
			pts[1]= curvV[i];
			Point** droite = new Point*[50];
			droite = BezierCurveByCasteljau(pts,2,50);
			surf[i]= new Point*[50];
			for(int j =0;j<50;j++){
				surf[i][j] = new Point(droite[j]->getX(),droite[j]->getY(),droite[j]->getZ());
				glColor3f(1.0,1.0,1.0);
				glPointSize(2);
      			glBegin(GL_POINTS);
      				glVertex3f(surf[i][j]->getX(),surf[i][j]->getY(),surf[i][j]->getZ());
      			glEnd();
				
			}
			

	}

	
	return surf;
}


Point** BezierSurfaceByCasteljau(Point** tabControlPointU, long nbControlPointU, long nbU,Point** tabControlPointV, long nbControlPointV,long nbV){
	Point** courbeU = BezierCurveByCasteljau(tabControlPointU,nbControlPointU,nbU);
	Point** courbeV = BezierCurveByCasteljau(tabControlPointV,nbControlPointV,nbV);

	Point** surf = new Point*[nbV*nbU];

	for(int i = 0;i<nbU;i++){
		for(int j =0;j<nbV;j++){

		}
	}
}
