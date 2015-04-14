#include "voxel.h"

//using namespace std;


Voxel::Voxel(Point* centre, double length){
	this->centre = new Point(*centre);
	this->length = length;
	size=0;
	
}

Voxel** Voxel::getSousVoxel(){
	return this->sousVox;
}

void Voxel::setSousVoxel(Voxel** pts, long nbVox){
	sousVox = pts;
	size = nbVox;
}

Point* Voxel::getCentre(){
	return this->centre;
}

double Voxel::getLength(){
	return this->length;
}

long Voxel::getSize(){
	return this->size;
}

Point** Voxel::getAngles(){
	Point** pts = new Point*[8];
	pts[0] = new Point(getCentre()->getX()-getLength()/2,
						getCentre()->getY()+getLength()/2,
						getCentre()->getZ()-getLength()/2);
	pts[1] = new Point(getCentre()->getX()+getLength()/2,
						getCentre()->getY()+getLength()/2,
						getCentre()->getZ()-getLength()/2);
	pts[2] = new Point(getCentre()->getX()-getLength()/2,
						getCentre()->getY()-getLength()/2,
						getCentre()->getZ()-getLength()/2);
	pts[3] = new Point(getCentre()->getX()+getLength()/2,
						getCentre()->getY()-getLength()/2,
						getCentre()->getZ()-getLength()/2);

	pts[4] = new Point(getCentre()->getX()-getLength()/2,
						getCentre()->getY()+getLength()/2,
						getCentre()->getZ()+getLength()/2);
	pts[5] = new Point(getCentre()->getX()+getLength()/2,
						getCentre()->getY()+getLength()/2,
						getCentre()->getZ()+getLength()/2);
	pts[6] = new Point(getCentre()->getX()-getLength()/2,
						getCentre()->getY()-getLength()/2,
						getCentre()->getZ()+getLength()/2);
	pts[7] = new Point(getCentre()->getX()+getLength()/2,
						getCentre()->getY()-getLength()/2,
						getCentre()->getZ()+getLength()/2);
	return pts;
}

/*Point** Voxel::getSousSommet(){
	Point** pts = new Point*[8];
	pts[0] = new Point(getCentre()->getX()-getLength()/4,
						getCentre()->getY()+getLength()/4,
						getCentre()->getZ()-getLength()/4);
	pts[1] = new Point(getCentre()->getX()+getLength()/4,
						getCentre()->getY()+getLength()/4,
						getCentre()->getZ()-getLength()/4);
	pts[2] = new Point(getCentre()->getX()-getLength()/4,
						getCentre()->getY()-getLength()/4,
						getCentre()->getZ()-getLength()/4);
	pts[3] = new Point(getCentre()->getX()+getLength()/4,
						getCentre()->getY()-getLength()/4,
						getCentre()->getZ()-getLength()/4);

	pts[4] = new Point(getCentre()->getX()-getLength()/4,
						getCentre()->getY()+getLength()/4,
						getCentre()->getZ()+getLength()/4);
	pts[5] = new Point(getCentre()->getX()+getLength()/4,
						getCentre()->getY()+getLength()/4,
						getCentre()->getZ()+getLength()/4);
	pts[6] = new Point(getCentre()->getX()-getLength()/4,
						getCentre()->getY()-getLength()/4,
						getCentre()->getZ()+getLength()/4);
	pts[7] = new Point(getCentre()->getX()+getLength()/4,
						getCentre()->getY()-getLength()/4,
						getCentre()->getZ()+getLength()/4);
	return pts;
}*/

void Voxel::decouper(){
	Voxel** ssVox = new Voxel*[8];
	Point** pts = getAngles();
	for(int i =0; i<8;i++){
		ssVox[i]=new Voxel(pts[i],this->getLength()/2);
	}
	setSousVoxel(ssVox,8);

}	