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
                Patch();
                Patch(vector<Point> p);
                void multMatrixVector(float *m, float *v, float *res);
                vector<Point> getPatchPoints(int patch);
                Point* getPoint(float ta, float tb, float coordenadasX[4][4], float coordenadasY[4][4], float coordenadasZ[4][4]);
                void parserPatchFile(string filename);
                Patch(int tess, string filename);
                vector<Point> geradorModeloBezier();

};

#endif
