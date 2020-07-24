#pragma once

#include <string>

class Shape {
  public:
    Shape(std::string t, int s);

    int getSides();

    std::string getType();

    const virtual double getArea() = 0;

    const virtual double getPerimeter() = 0;

    std::string toString();

  protected:
    std::string m_type;
    int m_sides;
};
