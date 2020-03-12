#include "headers/Shape.h"

Shape::Shape(){}

Shape::Shape(vector<Point*> p){
    points = p;
}

vector<Point*> Shape::getPoints() {
    return points;
}