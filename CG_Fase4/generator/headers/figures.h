#ifndef FIGURES_FIGURES_H
#define FIGURES_FIGURES_H

#include <vector>
#include "Point.h"

using namespace std;

vector<Point> box(float length, float width, float height, int nDivisions, vector<Point> *normal, vector<float> *texture);
Point drawPoints(float radius, float angle, float height);
vector<Point> cylinder(float radius, float height, int slices, int layers, vector<Point> *normal, vector<float> *texture);
Point pointsSphere(float radius, float beta, float alfa);
vector<Point> sphere(float radius, int slices, int layers,vector<Point> *normal, vector<float> *texture);
vector<Point> plane(float size,vector<Point> *normal, vector<float> *texture);
vector<Point> cone(float radius, float height, int slices, int layers, vector<Point> *normal, vector<float> *texture);
vector<Point> torus(float radiusIn, float radiusOut, int slices, int layers,vector<Point> *normal, vector<float> *texture);
#endif
