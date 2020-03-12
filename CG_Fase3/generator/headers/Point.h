#ifndef POINT_POINT_H
#define POINT_POINT_H

#include <math.h>
#include <string> 

using namespace std;

class Point{

	public:
		float x;
		float y;
		float z;
		Point();
		Point(float,float,float);
		float getX();
		float getY();
		float getZ();
};

#endif
