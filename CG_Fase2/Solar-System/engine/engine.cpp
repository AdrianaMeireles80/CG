#include <stdlib.h>
#include "headers/tinyxml2.h"
#include "headers/engine.h"
#include "headers/Point.h"
#include "headers/parser.h"

using namespace std;
using namespace tinyxml2;

void drawSystem(Group *system)
{
    glPushMatrix();
    const char* type;
    glColor3f(0.5f, 0.5f, 1.0f);
    for (Transformation *t: system->getTransformations()){
        type = t->getType().c_str();
        if(!strcmp(type,"translation")) {
            glTranslatef(t->getX(), t->getY(), t->getZ());
        }


        else if(!strcmp(type, "rotation")) {
            glRotatef(t->getAngle(),
                      t->getX(),
                      t->getY(),
                      t->getZ());
        }

        else if(!strcmp(type,"scale")) {
            glScalef(t->getX(), t->getY(), t->getZ());
        }
	else if(!strcmp(type,"colour")) {
            glColor3f(t->getX(), t->getY(), t->getZ());
        }
    }

    glBegin(GL_TRIANGLES);
    for (Shape *shape : system->getShapes()){

        for (Point *p : shape->getPoints())
            glVertex3f(p->getX(), p->getY(), p->getZ());
    }
    glEnd();

    for (Group *g : system->getGroups())
        drawSystem(g);

    glPopMatrix();
}

void drawOrbits()
{
    glColor3f(1.0f, 1.0f, 0.94f);

    for(auto const& p : orbits){
        glBegin(GL_POINTS);
        for (int j = 0 ; j < 200 ; j++)
        {
            float x = p->getX() * p->getX();
            float y = p->getY() * p->getY();
            float z = p->getZ() * p->getZ();
            float radius = sqrtf(x + y + z);
            float alpha = j * 2 * M_PI / 200;
            glVertex3f(radius * cos(alpha), 0, radius * sin(alpha));
        }
        glEnd();
    }
}

void MenuAjuda() {
	cout << "#_____________________________ HELP _____________________________#" << endl;
	cout << "| Usage: ./engine {XML FILE}                                     |" << endl;
	cout << "|                 [-h]                                           |" << endl;
	cout << "|   FILE:                                                        |" << endl;
	cout << "| Specify a path to an XML file in which the information about   |" << endl;
	cout << "| the models you wish to create are specified                    |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ↑ : Rotate your view up                                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ↓ : Rotate your view down                                    |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ← : Rotate your view to the left                             |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   → : Rotate your view to the right                            |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   F1 : Increase image                                          |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   F2 : Decrease image                                          |" << endl;
	cout << "|                                                                |" << endl;
    cout << "|   F6 : Reset zoom                                              |" << endl;
    cout << "|                                                                |" << endl;
	cout << "|   FORMAT:                                                      |" << endl;
	cout << "|   F3: Change the figure format into points                     |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   F4: Change the figure format into lines                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   F5: Fill up the figure                                       |" << endl;
	cout << "#________________________________________________________________#" << endl;
}

void processMenu(int option)
{
    switch (option)
    {
        case 0:
            exit(0);
        case 1:
            camera->posInitialCamera();
            break;
        default:
        {
            Point *p = orbits.at(option - 2);
            camera->changePositionLook(p->getX(),p->getY(),p->getZ());
            break;
        }
    }
    glutPostRedisplay();
}

void showMenu()
{
    int planet = glutCreateMenu(processMenu);
    glutAddMenuEntry("Sun",1);
    for (int op = 0; op < (int)orbits.size(); op++)
    {
        char str[10];
        sprintf(str, "Planet %d", op+1);
        glutAddMenuEntry(str, op+2);
    }

    glutCreateMenu(processMenu);
    glutAddSubMenu("Planet ",planet);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void specialKey (int key, int a, int b)
{
    (void) a, (void) b;
    switch(key){
        case GLUT_KEY_F3:
            line = GL_POINT;
            break;
        case GLUT_KEY_F4:
            line = GL_LINE;
            break;
        case GLUT_KEY_F5:
            line = GL_FILL;
            break;
        default:
            camera->specialKeyCamera(key);
    }
    glutPostRedisplay();
}

void mousePress(int button, int state, int x, int y)
{
    camera->mousePress(button,state,x,y);
}

void mouseMotion(int x, int y)
{
    camera->mouseMotion(x,y);
}

void renderScene(void)
{

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt (
            camera->getXPosition(), camera->getYPosition(), camera->getZPosition(),
            camera->getXLook(), camera->getYLook(), camera->getZLook(),
            0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, line);
    drawSystem(scene);
    drawOrbits();


    // End of frame
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("SOLAR_SYSTEM");

    if (argc < 2) {
        cout << "Invalid input. Use -h if you need some help." << endl;
        return 0;
    }
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "-help")) {
        MenuAjuda();
        return 0;
    }
    scene = loadXMLfile(argv[1], &orbits);
    camera = new Camera();
    if(scene == nullptr) return 0;
    // put GLUT init here

    // put callback registration here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(specialKey);

    // Mouse
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseMotion);

    showMenu();
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}
