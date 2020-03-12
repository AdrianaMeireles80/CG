#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H


#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Point.h"
#include "Group.h"
#include "Camera.h"

using namespace std;

int line = GL_LINE;
Group *scene;
Camera *camera;
float eTime = 0.0f, cTime = 0.0f;
int frame = 0, timebase = 0;
int stop;

void specialKey(int key, int a, int b);
void renderScene(void);
void changeSize(int w, int h);
void MenuAjuda();


#endif //ENGINE_ENGINE_H
