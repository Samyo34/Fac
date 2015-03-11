#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    Vector(Vector &p);
    double getX();
    double getY();
    double getZ();
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    double norme();
    void normalize();
    double scalar(Vector vector2);
    Vector* vectoriel(Vector vector2);
    double angle(Vector vector2);

private:
    double x,y,z;
};

#endif // VECTOR_H
