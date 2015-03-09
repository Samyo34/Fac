#include <iostream>
#include <stdio.h>
#include "point.h"
#include "vector.h"
#include "./TP_OPENGL"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Point a(2,1,0);
    Point b(4,1,0);
    Point c(3.5,3.5,0);
    Point c2;
    c2 = c.projectOnLine(a,b);
    std::cout<<"x: "<<c2.getX()<<" y: "<<c2.getY()<<" z: "<<c2.getZ()<<std::endl;

    Point d(0,0,0);
    Point p(1,1,1);
    Vector v(0,0,1);

    Point p2;
    p2 = p.projectOnPlan(d,v);
    std::cout<<"x: "<<p2.getX()<<" y: "<<p2.getY()<<" z: "<<p2.getZ()<<std::endl;



    return 0;
}

