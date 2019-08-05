#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape {
public:
  Triangle();
  Triangle(double base, double height);
  double perimeter() const override;
  double area() const override;

private:
  double m_base;
  double m_height;
};
#endif // TRIANGLE_H
