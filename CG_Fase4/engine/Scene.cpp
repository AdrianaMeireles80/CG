#include "headers/Scene.h"

Scene::Scene(Group *group) {
    mainGroup = group;
}

void Scene::addLight(Light *l)
{
    glEnable(GL_LIGHT0 + (GLenum) lights.size());
    lights.push_back(l);
}

void Scene::applyLights()
{
    GLenum number = 0;
    for(Light *l : lights)
        l->apply(number++);
}

Group* Scene::getMainGroup() {
    return mainGroup;
}