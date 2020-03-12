#ifndef POINT_POINT_H
#define POINT_POINT_H

#include <math.h>
#include <string> 

using namespace std;

class Point{

	private:
		float x;
		float y;
		float z;

	public:
		Point();
		Point(float,float,float);
		float getX();
		float getY();
		float getZ();
                void setX(float px);
		void setY(float py);
		void setZ(float pz);
};

#endif
