#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Point.h"
#include "Transformation.h"

using namespace std;

class Material{

    float diffuse[4];     // default: {0.8, 0.8, 0.8, 1};
    float ambient[4];     // default: {0.2, 0.2, 0.2, 1};
    float specular[4];     // default: {0, 0, 0, 1};
    float emission[4];     // default: {0, 0, 0, 1};

public:
    Material();
    Material(Transformation* d, Transformation* a, Transformation* s, Transformation* e);
    void draw();
    float* getDiffuse();
    float* getAmbient();
    float* getSpecular();
    float* getEmission();
};

#endif