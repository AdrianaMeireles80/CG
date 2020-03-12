
#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Point.h"
#include <vector>

#define POINT 1
#define DIRECTIONAL 2

#define DIFFUSE 3
#define AMBIENT 4
#define SPECULAR 5
#define EMISSION 6

using namespace std;

class Light {
    private:
        float *info;
        vector<int> attributes;
        int i = 0;

    public:
        Light();
        Light(float *inf, vector<int> atrb);
        void apply(GLenum number);
};

#endif //ENGINE_LIGHT_H
