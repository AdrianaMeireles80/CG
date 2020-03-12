#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H


class Camera {

private:
    float radius, speed;
    float alpha, teta;
    float positionX, positionY, positionZ;
    float lookX, lookY, lookZ;

    float mousePositionX, mousePositionY;
    bool mouseLeftIsPressed;

public:
    Camera();
    float getXPosition();
    float getYPosition();
    float getZPosition();
    float getXLook();
    float getYLook();
    float getZLook();
    void posInitialCamera();
    void changePositionLook(float x, float y, float z);
    void specialKeyCamera(int key);
    void mousePress(int button, int state, int x, int y);
    void mouseMotion(int xx, int yy);
};


#endif //ENGINE_CAMERA_H
