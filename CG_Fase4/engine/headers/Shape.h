#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include "Point.h"
#include "Material.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#endif

using namespace std;

class Shape {
    private:
        int numVertex[3];
        GLuint buffer[3];
        GLuint text;
        Material* m;

    public:
        Shape(vector<Point*> vertex, vector<Point*> normal, vector<float> texture);
        void setParseMat(Material* c);
        Shape(string textureFile, vector<Point*> vertex, vector<Point*> normal, vector<float> texture);
        void loadTexture(string textureFile);
        GLuint* getBuffer();
        GLuint getTexture();
        void setTexture(GLuint text);
        void prepareBuffer(vector<Point*> vertex, vector<Point*> normal, vector<float> texture);
        void draw();
};


#endif //ENGINE_SHAPE_H
