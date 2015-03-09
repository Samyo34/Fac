#ifndef POINT_H
#define POINT_H
#include "vector.h"


class Point
{
public:
    Point();
    Point(double x, double y, double z);
    Point(Point &p);
    double getX();
    double getY();
    double getZ();
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    Point projectOnLine(Point point1Line, Point point2Line);
    Point projectOnLine(Vector vecteur, Point pLine);
    Point projectOnPlan(Point poinOnPlane, Vector normalOfPlane);

private:
    double x,y,z;
};

#endif // POINT_H
