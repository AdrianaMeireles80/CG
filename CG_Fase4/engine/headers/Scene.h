#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "Light.h"
#include "Group.h"

using namespace std;

class Scene {
    private:
        vector<Light*> lights;
        Group *mainGroup;
    public:
    Scene(Group *group);
    void addLight(Light *l);
    void applyLights();
    Group* getMainGroup();
};


#endif //ENGINE_SCENE_H
