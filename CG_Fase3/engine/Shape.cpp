#include "headers/Shape.h"

Shape::Shape(){}

Shape::Shape(vector<Point*> vertex){
    numVertex = vertex.size();
    prepareBuffer(vertex);
}

void Shape::prepareBuffer(vector<Point*> vertex){
    int index = 0;
    float* vertexs = new float[vertex.size() * 3];
    for(vector<Point*>::const_iterator vertex_it = vertex.begin(); vertex_it != vertex.end(); ++vertex_it){
        vertexs[index++] = (*vertex_it)->getX();
        vertexs[index++] = (*vertex_it)->getY();
        vertexs[index++] = (*vertex_it)->getZ();
    }
    glGenBuffers(1,bufferVertex);
    glBindBuffer(GL_ARRAY_BUFFER, bufferVertex[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * numVertex * 3,
                 vertexs,
                 GL_STATIC_DRAW);
    delete [] vertexs;
}

void Shape::draw(){
    glBindBuffer(GL_ARRAY_BUFFER, bufferVertex[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, numVertex * 3);
}