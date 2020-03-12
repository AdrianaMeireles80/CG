#include <vector>
#include "headers/Point.h"
#include "headers/Light.h"

Light::Light(){}

Light::Light(float *inf, vector<int> atrb)
{
    info = inf;
    attributes = atrb;
}

void Light::apply(GLenum number)
{
        // LIGHT POSITION
        glLightfv(GL_LIGHT0+number, GL_POSITION, info);

        // LIGHT ATTRIBUTES
        for (const int atrb : attributes)
        {
            switch(atrb)
            {
                case DIFFUSE:
                    glLightfv(GL_LIGHT0+number, GL_DIFFUSE, info+4);
                    break;

                case AMBIENT:
                    glLightfv(GL_LIGHT0+number, GL_AMBIENT, info+8);
                    break;

                case SPECULAR:
                    glLightfv(GL_LIGHT0+number, GL_SPECULAR, info+12);
                    break;
            }
        }
    }