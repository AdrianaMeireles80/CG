#include "headers/Group.h"

Group::Group(){}

void Group::addTransformation(Transformation* t){
    transformations.push_back(t);
}

void Group::addGroup(Group* g){
    groups.push_back(g);
}

void Group::setShapes(vector<Shape*> pt){
    shapes = pt;
}

vector<Shape*> Group::getShapes() {
    return shapes;
}

vector<Group*>  Group:: getGroups() {
    return groups;
}

vector<Transformation*> Group::getTransformations() {
    return transformations;
}