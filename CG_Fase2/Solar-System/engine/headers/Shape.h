#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include "Point.h"
#include <vector>

using namespace std;

class Shape {
    private:
        vector<Point*> points;

    public:
        Shape();
        Shape(vector<Point*> p);
        vector<Point*> getPoints();
};


#endif //ENGINE_SHAPE_H
