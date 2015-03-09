#include "vector.h"

using namespace std;

Vector::Vector()
{
}

Vector::Vector(double x, double y, double z){
    this->x =x;
    this->y=y;
    this->z=z;
}

Vector::Vector(Vector &p){
    this->x =p.getX();
    this->y=p.getY();
    this->z=p.getZ();
}

double Vector::getX(){
    return this->x;
}

void Vector::setX(double x){
    this->x=x;
}

double Vector::getY(){
    return this->y;
}

void Vector::setY(double y){
    this->y=y;
}

double Vector::getZ(){
    return this->z;
}

void Vector::setZ(double z){
    this->z=z;
}

double Vector::norme(){
    double racine = sqrt(pow(this->getX(),2)+pow(this->getY(),2)+pow(this->getZ(),2));
    return racine;
}

void Vector::normalize(){
    double norme = this->norme();
    this->setX(this->getX()/norme);
    this->setY(this->getY()/norme);
    this->setZ(this->getZ()/norme);
}

double Vector::scalar(Vector vector2){
    return this->getX()*vector2.getX() + this->getY()*vector2.getY() + this->getZ()*vector2.getZ();
}

Vector *Vector::vectoriel(Vector vector2){
    double x = this->getY()*vector2.getZ() - this->getZ()*vector2.getY();
    double y = this->getZ()*vector2.getX() - this->getX()*vector2.getZ();
    double z = this->getX()*vector2.getY() - this->getY()*vector2.getX();
    Vector *vec = new Vector(x,y,z);
    return vec;

}

double Vector::angle(Vector vector2){
    return acos(this->scalar(vector2)/(this->norme()*vector2.norme()));
}
