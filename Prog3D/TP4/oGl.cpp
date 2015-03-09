#include "oGl.h"
#include <iostream>

using namespace std;

int a =2;

void drawCurve(Point** tabPointOfCurve, long nbPoint){
	glLineWidth(4);
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < nbPoint;i++){
        	glVertex3f(tabPointOfCurve[i]->getX(),tabPointOfCurve[i]->getY(),tabPointOfCurve[i]->getZ());
        }
    glEnd();
}

Point** HermiteCubicCurve(Point *p0, Point *p1, Vector *v0, Vector *v1, long nbU){

	Point** pts = new Point*[nbU];
	float u;
	double f1,f2,f3,f4;
	for(int i = 0; i<nbU;i++){
		u = 1/(float)nbU * (float)i;

		f1 = 2 * pow(u,3) - 3 * pow(u,2) + 1;
		f2 = -2 * pow(u,3)+ 3 * pow(u,2);
		f3 = pow(u,3) - 2 * pow(u,2) + u;
		f4 = pow(u,3) - pow (u,2);
		pts[i] = new Point(f1 * p0->getX() + f2 * p1->getX() + f3*v0->getX() + f4*v1->getX(),
							f1 * p0->getY() + f2 * p1->getY() + f3*v0->getY() + f4*v1->getY(),
							f1 * p0->getZ() + f2 * p1->getZ() + f3*v0->getZ() + f4*v1->getZ());
	}

	return pts;

}

long fact(long nb){
	if(nb == 0){
		return 1;
	}else{
		return nb * fact(nb - 1);
	}
}


Point** BezierCurveByBernstein(Point** tabControlPoint, long nbControlPoint, long nbU){
	Point** pts = new Point*[nbU];
	float b,u;
	for(int i =0;i<nbU;++i){
		u = 1/(float)nbU * (float)i;
		float x=0;
		float y=0;
		float z=0;
		for(int j = 0; j <nbControlPoint;j++){
			b = (fact(nbControlPoint -1 )/(fact(j)*fact(nbControlPoint - j -1 ))) * pow(u,j) * pow ((1 - u),nbControlPoint-j);
			x += b * tabControlPoint[j]->getX();
			y += b * tabControlPoint[j]->getY();
			z += b * tabControlPoint[j]->getZ();
		}
		pts[i]= new Point((double)x,(double)y,(double)z);
		//cout<<x<<" "<<y<<" "<<z<<endl;;
	}
	pts[nbU] = new Point(tabControlPoint[nbControlPoint -1]->getX(),
							tabControlPoint[nbControlPoint - 1]->getY(),
							tabControlPoint[nbControlPoint - 1]->getZ());

	return pts;
}


Point* calc(Point** tabControlPoint, long nbControlPoint, float u){
	if(nbControlPoint == 1){
		a--;
		return new Point(tabControlPoint[0]->getX(),tabControlPoint[0]->getY(),tabControlPoint[0]->getZ());
		
	}else{
		Point* pts[nbControlPoint-1];
		float x, y,z;
		for(int i =0;i<nbControlPoint-1;i++){
			x = ((tabControlPoint[i+1]->getX() - tabControlPoint[i]->getX())*u) + tabControlPoint[i]->getX();
			y = ((tabControlPoint[i+1]->getY() - tabControlPoint[i]->getY())*u) + tabControlPoint[i]->getY();
			z = ((tabControlPoint[i+1]->getZ() - tabControlPoint[i]->getZ())*u) + tabControlPoint[i]->getZ();
			Point* p = new Point(x,y,z);
			pts[i]=p;
					if(a >0 ){
		glColor3f(0.0,0.0,0.0);
		glLineWidth(1);
    	glBegin(GL_LINES);
        	glVertex3f(tabControlPoint[i]->getX(),tabControlPoint[i]->getY(),tabControlPoint[i]->getZ());
        	glVertex3f(tabControlPoint[i+1]->getX(),tabControlPoint[i+1]->getY(),tabControlPoint[i+1]->getZ());
    	glEnd();
		}

		}

		return calc(pts,nbControlPoint -1,u);
	}
}


Point** BezierCurveByCasteljau(Point** tabControlPoint,long nbControlPoint,long nbU){
	Point ** pts = new Point*[nbU];
	a =2;
	float u;
	for(int i = 0;i<=nbU;i++){
		u = 1/(float)nbU * (float)i;
		pts[i]=calc(tabControlPoint,nbControlPoint,u);
	}
	return pts;
}
