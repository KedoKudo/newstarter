#ifndef SHAPESORTER_H
#define SHAPESORTER_H
#include "Circle.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Triangle.h"
#include <algorithm>
#include <iostream>
#include <vector>

class ShapeSorter {
public:
	//constructor for if no arguments are given
  ShapeSorter();
	//constructor for the given vector
  ShapeSorter(std::vector<Shape *> shapes);
	//function to print the type of the shapes in the vector
  void printType() const;
	//function to print the shapes with a number of sides equal to the number given as argument
  void printSide(int sides) const;
	//function to print the shapes in area descending order
  void printAreaDescending();
	//function to print the shapes in perimeter descending order
  void printPerimeterDescending();

private:
  std::vector<Shape *> m_shapes;
};
#endif // SHAPESORTER_H