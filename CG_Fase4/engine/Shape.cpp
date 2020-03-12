#include <IL/il.h>
#include "headers/Material.h"
#include "headers/Shape.h"


Shape::Shape(vector<Point*> vertex, vector<Point*> normal, vector<float> texture){
    numVertex[0] = vertex.size();
    numVertex[1] = normal.size();
    numVertex[2] = texture.size();
    prepareBuffer(vertex,normal,texture);
}

Shape::Shape(string textureFile, vector<Point*> vertex, vector<Point*> normal, vector<float> texture){
    numVertex[0] = vertex.size();
    numVertex[1] = normal.size();
    numVertex[2] = texture.size();
    prepareBuffer(vertex,normal,texture);
    loadTexture(textureFile);
}

void Shape::setParseMat(Material* c){
	m = c;
}

void Shape::prepareBuffer(vector<Point*> vertex, vector<Point*> normal, vector<float> texture){
    int index = 0;
    float* vertexs = new float[vertex.size() * 3];
    for(vector<Point*>::const_iterator vertex_it = vertex.begin(); vertex_it != vertex.end(); ++vertex_it){
        vertexs[index++] = (*vertex_it)->getX();
        vertexs[index++] = (*vertex_it)->getY();
        vertexs[index++] = (*vertex_it)->getZ();
    }
    index = 0;
    float* normals = new float[normal.size() * 3];
    for(vector<Point*>::const_iterator vertex_it = normal.begin(); vertex_it != normal.end(); ++vertex_it){
        normals[index++] = (*vertex_it)->getX();
        normals[index++] = (*vertex_it)->getY();
        normals[index++] = (*vertex_it)->getZ();
    }

    glGenBuffers(3,buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * numVertex[0] * 3,
                 vertexs,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * numVertex[1] * 3,
                 normals,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * numVertex[2],
                 &(texture[0]),
                 GL_STATIC_DRAW);

    free(vertexs);
    free(normals);
  //  delete [] vertexs;
  //  delete [] normals;
}

GLuint* Shape::getBuffer(){
    return buffer;
}

GLuint Shape::getTexture(){
    return text;
}

void Shape::setTexture(GLuint t){
    text = t;
}

void Shape::loadTexture(string textureFile){
    unsigned int t,tw,th;
    unsigned char *texData;

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) textureFile.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shape::draw(){

    m->draw();

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    if(numVertex[1] > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
    }

    if(numVertex[2] > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, text);
    }

   // glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, (numVertex[0]) * 3);
   // glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);

    //   glDeleteBuffers(1, bufferVertex);
}
