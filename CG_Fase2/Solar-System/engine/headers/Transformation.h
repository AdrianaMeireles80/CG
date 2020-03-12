#ifndef TRANFORMATION_TRANSFORMATION_H
#define TRANFORMATION_TRANSFORMATION_H
#include<string>

using namespace std;

class Transformation
{
    private:
        string type;
        float angle;
        float x;
        float y;
        float z;

    public:
        Transformation();
        Transformation(string typeT, float a, float xx, float yy, float zz);
        string getType();
        float getAngle();
        float getX();
        float getY();
        float getZ();
};

#endif
