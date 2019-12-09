#ifndef CIRCLE_H
#define CIRCLE_H

#include<cmath>

#include "shape.h"

using namespace std;

class Circle : public Shape
{
public:
    double radius;

    Circle();
    Circle(double r);

    double area();
    double perimeter();
};

ostream& operator<<(ostream &os, const Circle &c);

#endif // CIRCLE_H