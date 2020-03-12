#ifndef FIGURES_FIGURES_H
#define FIGURES_FIGURES_H

#include <vector>

using namespace std;

typedef struct point {
	float x;
	float y;
	float z;
} Point;

vector<Point> box(float length, float width, float height, int nDivisions);
Point drawPoints(float radius, float angle, float height);
vector<Point> cone(float radius, float height, int slices, int layers);
Point pointsSphere(float radius, float beta, float alfa);
vector<Point> sphere(float radius, int slices, int layers);
vector<Point> plane(float size);
vector<Point> cylinder(float radius, float height, int slices, int layers);

#endif
