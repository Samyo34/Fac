#include "voxel.h"

#include <math.h>
using namespace std;
int cpt;

void displayVoxel(Point* centre, double length){
	/*Point* p1 = new Point(centre->getX()-(length/2),centre->getY()+length/2,centre->getZ()+length/2);
	Point* p2 = new Point(centre->getX()+length/2,centre->getY()+length/2,centre->getZ()+length/2);
	Point* p3 = new Point(centre->getX()+length/2,centre->getY()-(length/2),centre->getZ()+length/2);
	Point* p4 = new Point(centre->getX()-(length/2),centre->getY()-(length/2),centre->getZ()+length/2);

	Point* p5 = new Point(centre->getX()-(length/2),centre->getY()+length/2,centre->getZ()-length/2);
	Point* p6 = new Point(centre->getX()+length/2,centre->getY()+length/2,centre->getZ()-length/2);
	Point* p7 = new Point(centre->getX()+length/2,centre->getY()-(length/2),centre->getZ()-length/2);
	Point* p8 = new Point(centre->getX()-(length/2),centre->getY()-(length/2),centre->getZ()-length/2);*/
	
	Point* p1 = new Point(centre->getX()-(length),centre->getY()+length,centre->getZ()+length);
	Point* p2 = new Point(centre->getX()+length,centre->getY()+length,centre->getZ()+length);
	Point* p3 = new Point(centre->getX()+length,centre->getY()-(length),centre->getZ()+length);
	Point* p4 = new Point(centre->getX()-(length),centre->getY()-(length),centre->getZ()+length);

	Point* p5 = new Point(centre->getX()-(length),centre->getY()+length,centre->getZ()-length);
	Point* p6 = new Point(centre->getX()+length,centre->getY()+length,centre->getZ()-length);
	Point* p7 = new Point(centre->getX()+length,centre->getY()-(length),centre->getZ()-length);
	Point* p8 = new Point(centre->getX()-(length),centre->getY()-(length),centre->getZ()-length);

	glPointSize(5);
	glBegin(GL_POLYGON);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glVertex3f(p4->getX(),p4->getY(),p4->getZ());
	glVertex3f(p8->getX(),p8->getY(),p8->getZ());
	glVertex3f(p5->getX(),p5->getY(),p5->getZ());
	glVertex3f(p1->getX(),p1->getY(),p1->getZ());
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glVertex3f(p3->getX(),p3->getY(),p3->getZ());
	glVertex3f(p7->getX(),p7->getY(),p7->getZ());
	glVertex3f(p6->getX(),p6->getY(),p6->getZ());
	glVertex3f(p2->getX(),p2->getY(),p2->getZ());
	glEnd();
}

bool intersect(Point* point, Point* centre, double rayon){
	double x = centre->getX()-point->getX();
	double y = centre->getY()-point->getY();
	double z = centre->getZ()-point->getZ();
	Vector v(x,y,z);
	cout<<v.norme()<<" | "<<fabs(x)<<":"<<fabs(y)<<":"<<fabs(z)<<" | "<<rayon<<endl;
	if(v.norme()<rayon){
		return true;
	}else{
		return false;
	}
}


int voxelIntersect(Voxel* v, Point* centre, double rayon){
	Point** pts = v->getAngles();
	int cpt=0;
	for(int i =0; i< 8; i++){
		//cout<<pts[i]->getX()<<":"<<pts[i]->getY()<<":"<<pts[i]->getZ()<<endl;
		if(intersect(pts[i],centre,rayon)!=0){
			cpt++;
		}
	}
	//cout<<cpt<<endl;
	return cpt;
}

void octree(Voxel* v, Point* centre, double rayon, double resolution){
	Voxel** ssVox;
	//cout<<v->getCentre()->getX()<<":"<<v->getCentre()->getY()<<":"<<v->getCentre()->getZ()<<endl;
	int res = voxelIntersect(v,centre,rayon);
	if(res>=2){
		if(v->getLength() <= resolution){
			displayVoxel(v->getCentre(),v->getLength());
		}else{
			v->decouper();
			ssVox = v->getSousVoxel();
			for(int i=0;i < (v->getSize());i++){
				octree(ssVox[i],centre,rayon,resolution);
			}
		}
	}


	/*if(!(res == 8)){
		if(v->getLength()>resolution){
			v->decouper();
			ssVox = v->getSousVoxel();
			for(int i=0;i < (v->getSize());i++){
				octree(ssVox[i],centre,rayon,resolution);
			}
		}
		
	}else{
		displayVoxel(v->getCentre(),v->getLength()/2);
	}*/

}


void displaySphereVolumic(Point* centre,double rayon, double resolution){
	// Création du cube à "découper"
	//cout<<centre->getX()<<endl;
	Voxel* v = new Voxel(centre, rayon);
	//cout<<"1 "<<v->getCentre()->getX()<<":"<<v->getCentre()->getY()<<":"<<v->getCentre()->getZ()<<endl;
	v->decouper();
	Voxel** ssV = v->getSousVoxel();
	//displayVoxel(v->getCentre(),rayon);
	
	octree(v,centre,rayon,resolution);

	/*for(int i =0; i<v->getSize();i++){
		//cout<<i<<" "<<ssV[i]->getCentre()->getX()<<":"<<ssV[i]->getCentre()->getY()<<":"<<ssV[i]->getCentre()->getZ()<<endl;
		octree(ssV[i],centre,rayon,resolution);
		//displayVoxel(ssV[i]->getCentre(),ssV[i]->getLength());
	}*/
	//octree(v,centre,rayon,resolution);
	
}

