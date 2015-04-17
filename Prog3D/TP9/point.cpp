#include "point.h"
#include <cmath>
#include <iostream>

Point::Point()
{
}

Point::Point(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(Point &p){
    this->x=p.getX();
    this->y=p.getY();
    this->z=p.getZ();
}

double Point::getX(){
    return this->x;
}

void Point::setX(double x){
    this->x=x;
}

double Point::getY(){
    return this->y;
}

void Point::setY(double y){
    this->y=y;
}

double Point::getZ(){
    return this->z;
}

void Point::setZ(double z){
    this->z=z;
}


Point Point::projectOnLine(Point point1Line, Point point2Line){
    Vector vBC(point2Line.getX()-point1Line.getX(),point2Line.getY()-point1Line.getY(),point2Line.getZ()-point1Line.getZ());
    Vector vBA(point1Line.getX()-this->getX(),point1Line.getY()-this->getY(),point1Line.getZ()-this->getZ());
    vBC.normalize();
    double dist = std::abs(vBA.scalar(vBC));
    double x = point1Line.getX() + vBC.getX() * dist;
    double y = point1Line.getY() + vBC.getY() * dist;
    double z = point1Line.getZ() + vBC.getZ() * dist;
    Point p(x,y,z);
    return p;
}

Point Point::projectOnLine(Vector vecteur, Point pLine){
    Vector vBA(pLine.getX()-this->getX(),pLine.getY()-this->getY(),pLine.getZ()-this->getZ());
    vecteur.normalize();
    double dist = std::abs(vBA.scalar(vecteur));
    double x = pLine.getX() + vecteur.getX() * dist;
    double y = pLine.getY() + vecteur.getY() * dist;
    double z = pLine.getZ() + vecteur.getZ() * dist;
    Point p(x,y,z);
    return p;
}

Point Point::projectOnPlan(Point pointOnPlane, Vector normalOfPlane){
    Vector vM(this->getX(),this->getY(),this->getZ());
    Vector vA(pointOnPlane.getX(),pointOnPlane.getY(),pointOnPlane.getZ());
    Vector vAM(vA.getX()-vM.getX(),vA.getY()-vM.getY(),vA.getZ()-vM.getZ());
    normalOfPlane.normalize();
    double scal = std::abs(vAM.scalar(normalOfPlane));
    double x = this->getX() - normalOfPlane.getX() * scal;
    double y = this->getY() - normalOfPlane.getY() * scal;
    double z = this->getZ() - normalOfPlane.getZ() * scal;

    Point p(x,y,z);
    return p;
}
