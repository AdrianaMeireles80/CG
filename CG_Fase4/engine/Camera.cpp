#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/Camera.h"

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4


Camera::Camera()
{
    posInitialCamera();
}

float Camera::getXPosition() { return positionX; }
float Camera::getYPosition() { return positionY; }
float Camera::getZPosition() { return positionZ; }
float Camera::getOrX() { return positionX + lookX; }
float Camera::getOrY() { return positionY + lookY; }
float Camera::getOrZ() { return positionZ + lookZ; }


void Camera::posInitialCamera()
{
    
    alpha = 0.0f, teta = -M_PI / 6.0f;

    positionX = -100.0f; positionY = 60.0f; positionZ = 0.0f;
    lookX = float(cos(teta)*cos(alpha)) ;
    lookY = float(sin(teta));
    lookZ = float(cos(teta)*sin(alpha));

    mouseLeftIsPressed = false;
}

void cross(float* a, float* b, float* res){
    res[0] = a[1] * b[2] -a[2] * b[1];
    res[1] = a[2] * b[0] -a[0] * b[2];
    res[2] = a[0] * b[1] -a[1] * b[0];
}
        void Camera::specialKeyCamera(int key)
        {
            switch (key)
            {
                case GLUT_KEY_F7:
                {
                    positionX += lookX * 1.7f;
                    positionY += lookY * 1.7f;
                    positionZ += lookZ * 1.7f;
                    break;
                }
                case GLUT_KEY_F8:
                {
                   positionX -= lookX * 1.7f;
                    positionY -= lookY * 1.7f;
                    positionZ -= lookZ * 1.7f;
                    break;
                }
                case GLUT_KEY_F9:
                {
                    float up[3], dir[3];
                    up[0] = up[2] = 0;
                    up[1] = 1;
                    dir[0] = lookX ;
                    dir[1] = lookY ;
                    dir[2] = lookZ;
                    float res[3];

                    cross(dir,up,res);

                    positionX -=  res[0] * 1.7f;
                    positionY -= res[1] * 1.7f;
                    positionZ -= res[2] * 1.7f;
                    break;
                }
                case GLUT_KEY_F10:
                {
                    float up[3], dir[3];
                    up[0] = up[2] = 0;
                    up[1] = 1;
                    dir[0] = lookX ;
                    dir[1] = lookY ;
                    dir[2] = lookZ;
                    float res[3];

                    cross(dir,up,res);

                    positionX +=  res[0] * 1.7f;
                    positionY += res[1] * 1.7f;
                    positionZ += res[2] * 1.7f;
                    break;
                }
                case GLUT_KEY_F6:
                    posInitialCamera();
                default:
                    break;
            }
        }


void Camera::mousePress(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            alpha += (x - mousePositionX) *  0.001f;
            teta += (y - mousePositionY) *  0.001f;
            mouseLeftIsPressed = false;
        }
 	else if (state == GLUT_DOWN)
        {
            glutSetCursor(GLUT_CURSOR_NONE);
            mousePositionX = x;
            mousePositionY = y;
            mouseLeftIsPressed = true;
        }
    }
    else if(button == GLUT_WHEEL_DOWN && state == GLUT_DOWN)
        positionY -= 0.5 * 1.7f;
    else if(button == GLUT_WHEEL_UP && state == GLUT_DOWN)
        positionY +=0.5 * 1.7f;

}


void Camera::mouseMotion(int x, int y)
{
    if (mouseLeftIsPressed)
    {
        float newAlpha, newTeta;

        newAlpha = alpha + (x - mousePositionX) * 0.001f;
        newTeta = teta + (y - mousePositionY) * 0.001f;

        if (newTeta > M_PI/2 - 0.05f) newTeta = M_PI/2 - 0.05f;
        else if (newTeta < -M_PI/2 + 0.05f) newTeta = -M_PI/2 + 0.05f;

        lookX = float(cos(newTeta)*cos(newAlpha));
        lookY = float(sin(newTeta));
        lookZ = float(cos(newTeta)*sin(newAlpha));
    }
}
