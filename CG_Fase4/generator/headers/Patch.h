#ifndef __PATCH_H__
#define __PATCH_H__

#include <vector>
#include <map>
#include "Point.h"
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

 class Patch{
                int nPatchs;
                int nPoints;
                int tessellation;
                vector<Point> controlPoints;
                map<int,vector<int> > patchs;

        public:
                float m[4][4] = {{-1.0f,  3.0f, -3.0f,  1.0f},
                      { 3.0f, -6.0f,  3.0f,  0.0f},
                      {-3.0f,  3.0f,  0.0f,  0.0f},
                      { 1.0f,  0.0f,  0.0f,  0.0f}};
                Patch();
                Patch(vector<Point> p);
                void multMatrixVector(float *m, float *v, float *res);
                float* getTangent(float tu, float tv, float mX[4][4], float mY[4][4], float mZ[4][4], int type);
                void normalize(float *a);
                void cross(float *a, float *b, float *res);
                void getPatchPoints(int patch, vector<Point>* points, vector<float>* textureList, vector<Point>* normalList);
                Point* getPoint(float ta, float tb, float coordenadasX[4][4], float coordenadasY[4][4], float coordenadasZ[4][4]);
                void parserPatchFile(string filename);
                Patch(int tess, string filename);
                void geradorModeloBezier(vector<Point> *vert, vector<Point> *normal, vector<float> *text);


};

#endif
