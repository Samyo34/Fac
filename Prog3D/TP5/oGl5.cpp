#include "voxel.h"
#include "vector.h"
#include "oGl5.h"

#include <math.h>
using namespace std;
int cpt;

void displayVoxel(Point* centre, double length){
	
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

	delete p1;delete p2;delete p3;delete p4;delete p5;delete p6;delete p7;delete p8;
}

bool intersect(Point* point, Point* centre, double rayon){
	double x = centre->getX()-point->getX();
	double y = centre->getY()-point->getY();
	double z = centre->getZ()-point->getZ();
	Vector v(x,y,z);
	//cout<<v.norme()<<" | "<<fabs(x)<<":"<<fabs(y)<<":"<<fabs(z)<<" | "<<rayon<<endl;
	if(v.norme()<=rayon){
		return true;
	}else{
		return false;
	}
}

/*
 * Retourne le nombre sommet qui intersect la sphere 
 */
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
	v->decouper();
	ssVox = v->getSousVoxel();
	int res = voxelIntersect(v,centre,rayon);
	if(res > 0 && res < 8)/* && !intersect(centre, centre,rayon)*/{
		if(v->getLength() >= resolution){
			for(int i=0;i < (v->getSize());i++){
				octree(ssVox[i],centre,rayon,resolution);
			}
		}else{
			displayVoxel(v->getCentre(),v->getLength());
		}
	}else if (res == 8){
		displayVoxel(v->getCentre(),v->getLength());
	}
}


void displaySphereVolumic(Point* centre,double rayon, double resolution){
	// Création du cube à "découper"
	//cout<<centre->getX()<<endl;
	Voxel* v = new Voxel(centre, rayon);
	//cout<<"1 "<<v->getCentre()->getX()<<":"<<v->getCentre()->getY()<<":"<<v->getCentre()->getZ()<<endl;
	v->decouper();
	Voxel** ssV = v->getSousVoxel();
	//displayVoxel(v->getCentre(),rayon);
	for(int i =0;i<v->getSize();i++){
		octree(ssV[i],centre,rayon,resolution);
	}
}

bool intersectCyl(Point* p, Point* axisOrigin, Vector* axisVector, double rayon){
	// TODO : calculer si p appartient au cylindre
	Vector v(axisOrigin->getX()-p->getX(),axisOrigin->getY()-p->getY(),axisOrigin->getZ()-p->getZ());
	Vector prodVec(v.getX()*axisVector->getZ()-v.getZ()*axisVector->getY(),
					v.getZ()*axisVector->getX()-v.getX()*axisVector->getZ(),
					v.getX()*axisVector->getY()-v.getY()*axisOrigin->getX());
	double distance = prodVec.norme()/axisVector->norme();
	//cout<<distance<<endl;
	if(distance <= rayon){
		return true;
	}else{
		return false;
	}
}

int voxelIntersectCyl(Voxel* v, Point* axisOrigin, Vector* axisVector, double rayon){
	Point** pts = v->getAngles();
	int res =0;
	for(int i =0; i<8;i++){
		if(intersectCyl(pts[i],axisOrigin,axisVector,rayon)){
			res++;
		}
	}
	return res;
}

void octreeCyl(Voxel* v, Point* axisOrigin, Vector* axisVector, double rayon, double resolution){
	Voxel** ssVox;
	//cout<<v->getCentre()->getX()<<":"<<v->getCentre()->getY()<<":"<<v->getCentre()->getZ()<<endl;
	v->decouper();
	ssVox = v->getSousVoxel();
	int res = voxelIntersectCyl(v,axisOrigin,axisVector,rayon);
	//cout<<res<<endl;

	if(res > 0 && res < 8){
		if(v->getLength() >= resolution){
			for(int i=0;i < (v->getSize());i++){
				octreeCyl(ssVox[i],axisOrigin,axisVector,rayon,resolution);
			}
		}else{
			displayVoxel(v->getCentre(),v->getLength());

		}
	}else if (res == 8){
		displayVoxel(v->getCentre(),v->getLength());
	}
}

void displayCylindreVolumic(Point* axisOrigin, Vector* axisVector, double rayon, double resolution){
	Voxel* v;
	if(rayon > axisVector->norme()){
		v = new Voxel(axisOrigin, rayon);
	}else{
		v = new Voxel(axisOrigin, axisVector->norme());
	}
	//displayVoxel(v->getCentre(),v->getLength());
	v->decouper();
	Voxel** ssVox = v->getSousVoxel();
	for(int i =0;i<8;i++){
		octreeCyl(ssVox[i],axisOrigin,axisVector,rayon,resolution);
	}
}



void octreeInter(Voxel* v, Point* centreSphere, double rayonSph, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution){
	Voxel** ssVox;
	v->decouper();
	ssVox = v->getSousVoxel();
	int resS = voxelIntersect(v,centreSphere,rayonSph);
	int resC = voxelIntersectCyl(v, axisOrigin,axisVectorOrigin,rayonCyl);
	//cout<<resS<<" "<<resC<<endl;
	if((resS>0 && resS<8) && (resC>0 && resC<8)){
		if(v->getLength()>=resolution){
			for(int i=0;i<(v->getSize());i++){
				octreeInter(ssVox[i],centreSphere,rayonSph,axisOrigin,axisVectorOrigin,rayonCyl,resolution);
			}
		}else{
			displayVoxel(v->getCentre(),v->getLength());
		}
	}else if((resS == 8 && (resC>2 && resC<8))||(resC == 8 && (resS>2 && resS<8))){
		displayVoxel(v->getCentre(),v->getLength());
	}

}

void display_INTERSECTION_sphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOriginCyl, Vector* axisVectorCyl, double rayonCyl, double resolution){
	Voxel* v;
	Point* centre = new Point((centreSphere->getX()+axisOriginCyl->getX())/2,(centreSphere->getY()+axisOriginCyl->getY())/2,(centreSphere->getZ()+axisOriginCyl->getZ())/2);
	if(rayonSphere>axisVectorCyl->norme() && rayonSphere>rayonCyl){
		v = new Voxel(centre,rayonSphere);
	}else if(rayonCyl>axisVectorCyl->norme()){
		v = new Voxel(centre,rayonCyl);
	}else{
		v = new Voxel(centre,axisVectorCyl->norme());
	}
	v->decouper();
	Voxel** ssVox = v->getSousVoxel();
	for(int i =0;i<8;i++){
		octreeInter(ssVox[i],centreSphere,rayonSphere,axisOriginCyl,axisVectorCyl,rayonCyl,resolution);
	}
}

void octreeSous(Voxel* v, Point* centreSphere,double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl,double resolution){
	Voxel** ssVox;
	v->decouper();
	ssVox = v->getSousVoxel();
	int resS = voxelIntersect(v,centreSphere,rayonSphere);
	int resC = voxelIntersectCyl(v, axisOrigin,axisVectorOrigin,rayonCyl);
	//cout<<resS<<" "<<resC<<endl;
	if((resS>0 && resS<8) && (resC<8)){
		if(v->getLength()>=resolution){
			for(int i=0;i<(v->getSize());i++){
				octreeSous(ssVox[i],centreSphere,rayonSphere,axisOrigin,axisVectorOrigin,rayonCyl,resolution);
			}
		}else if (resC==0){
			displayVoxel(v->getCentre(),v->getLength());
		}
	}else if(resS == 8 && resC==0){
		displayVoxel(v->getCentre(),v->getLength());
	}
}

void display_SOUSTRACTION_sphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution){
	Voxel* v;
	Point* centre = new Point((centreSphere->getX()+axisOrigin->getX())/2,(centreSphere->getY()+axisOrigin->getY())/2,(centreSphere->getZ()+axisOrigin->getZ())/2);
	if(rayonSphere>axisVectorOrigin->norme() && rayonSphere>rayonCyl){
		v = new Voxel(centre,rayonSphere);
	}else if(rayonCyl>axisVectorOrigin->norme()){
		v = new Voxel(centre,rayonCyl);
	}else{
		v = new Voxel(centre,axisVectorOrigin->norme());
	}

	v->decouper();
	Voxel** ssVox = v->getSousVoxel();
	for(int i =0;i<8;i++){
		octreeSous(ssVox[i],centreSphere,rayonSphere,axisOrigin,axisVectorOrigin,rayonCyl,resolution);
	}
}

void octreeUnion(Voxel* v, Point* centreSphere,double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl,double resolution){
	Voxel** ssVox;
	v->decouper();
	ssVox = v->getSousVoxel();
	int resS = voxelIntersect(v,centreSphere,rayonSphere);
	int resC = voxelIntersectCyl(v, axisOrigin,axisVectorOrigin,rayonCyl);
	if((resS>0 && resS<8) || (resC<8 && resC>0)){
		if(v->getLength()>resolution){
			for(int i=0;i<(v->getSize());i++){
				octreeUnion(ssVox[i],centreSphere,rayonSphere,axisOrigin,axisVectorOrigin,rayonCyl,resolution);
			}
		}else{
			displayVoxel(v->getCentre(),v->getLength());
		}
	}else if(resC==8 || resS == 8){
		displayVoxel(v->getCentre(),v->getLength());
	}
}

void display_UNION_SphereCylindre(Point* centreSphere, double rayonSphere, Point* axisOrigin, Vector* axisVectorOrigin, double rayonCyl, double resolution){
	Voxel* v;
	Point* centre = new Point((fabs(centreSphere->getX()-axisOrigin->getX()))/2,fabs(centreSphere->getY()-axisOrigin->getY())/2,
								fabs(centreSphere->getZ()-axisOrigin->getZ())/2);
	Vector vec1(centre->getX()-centreSphere->getX(),centre->getY()-centreSphere->getY(), centre->getZ()-centreSphere->getZ());
	Vector vec2(centre->getX()-axisOrigin->getX(),centre->getY()-axisOrigin->getY(), centre->getZ()-axisOrigin->getZ());
	double res;
	if(vec1.norme()>vec2.norme()){
		res = vec1.norme();
	}else{
		res = vec2.norme();
	}
	if(rayonSphere>axisVectorOrigin->norme() && rayonSphere>rayonCyl){
		v = new Voxel(centre,rayonSphere+res);
	}else if(rayonCyl>axisVectorOrigin->norme()){
		v = new Voxel(centre,rayonCyl+res);
	}else{
		v = new Voxel(centre,axisVectorOrigin->norme()+res);
	}

	v->decouper();
	Voxel** ssVox = v->getSousVoxel();
	for(int i =0;i<8;i++){
		octreeUnion(ssVox[i],centreSphere,rayonSphere,axisOrigin,axisVectorOrigin,rayonCyl,resolution);
	}
}