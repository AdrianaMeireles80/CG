#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "tinyxml2.h"
#include "Point.h"
#include "Group.h"
#include "Shape.h"
#include "Light.h"
#include "Scene.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

Scene* loadXMLfile(string filename);
void parseGroup (Scene *scene, Group *group, XMLElement *gElement);
void parseLights (Scene *scene, XMLElement *pElement);
void parseMaterial(Shape* shape, XMLElement* element);

#endif
