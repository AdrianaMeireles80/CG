#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/Camera.h"

Camera::Camera()
{
    posInitialCamera();
}

float Camera::getXPosition() { return positionX; }
float Camera::getYPosition() { return positionY; }
float Camera::getZPosition() { return positionZ; }
float Camera::getXLook() { return lookX; }
float Camera::getYLook() { return lookY; }
float Camera::getZLook() { return lookZ; }

void Camera::posInitialCamera()
{
    radius = 120.0f, speed = 0.5f;
    alpha = 4.3f, teta = 0.3f;

    lookX = 0; lookY = 0; lookZ = 0;
    positionX = lookX + radius*sin(alpha)*cos(teta);
    positionY = lookY + radius*sin(teta);
    positionZ = lookZ + radius*cos(alpha)*cos(teta);

    mouseLeftIsPressed = false;
}

void Camera::changePositionLook(float x, float y, float z)
{
    posInitialCamera();
    lookX = x;
    lookY = y;
    lookZ = z;

    positionX += x;
    positionY += y;
    positionZ += z;
}

void Camera::specialKeyCamera(int key)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            if (teta < (M_PI / 2 - speed))
                teta += speed;
            break;

        case GLUT_KEY_DOWN:
            if (teta > -(M_PI / 2 - speed))
                teta -= speed;
            break;

        case GLUT_KEY_LEFT:
            alpha -= speed;
            break;

        case GLUT_KEY_RIGHT:
            alpha += speed;
            break;

        case GLUT_KEY_F1:
            radius -= speed * 2;
            break;

        case GLUT_KEY_F2:
            radius += speed * 2;
            break;
        case GLUT_KEY_F6:
            posInitialCamera();
            break;
        default:
            break;
    }
    positionX = lookX + radius*sin(alpha)*cos(teta);
    positionY = lookY + radius*sin(teta);
    positionZ = lookZ + radius*cos(alpha)*cos(teta);
}

void Camera::mousePress(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            alpha += (x - mousePositionX) *  0.001f;
            teta += (y - mousePositionY) *  0.001f;
            mouseLeftIsPressed = false;
        }
 	else if (state == GLUT_DOWN)
        {
            mousePositionX = x;
            mousePositionY = y;
            mouseLeftIsPressed = true;
        }
    }
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

        positionX = lookX + radius * sin(newAlpha) * cos(newTeta);
        positionY = lookY + radius * sin(newTeta);
        positionZ = lookZ + radius * cos(newAlpha) * cos(newTeta);
    }
}
