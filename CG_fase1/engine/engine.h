#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct point {
	float x;
	float y;
	float z;
}Point;

int line = GL_LINE;
vector<Point> points;
float alpha = 0.7f, beta = 0.3f, radius = 10.0f, step = 0.08f;

void drawPrimitives(void);
int readPointsFile(string filename);
void specialKey(int key, int a, int b);
void renderScene(void);
void changeSize(int w, int h);
void MenuAjuda();


#endif //ENGINE_ENGINE_H
