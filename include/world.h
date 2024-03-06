#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "point.h"
#include "vbo.h"
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Window{
    public:
        int width;
        int height;
        Window();
        Window(int newHeight, int newWidth);
        Window(XMLElement *windowElement);
};

class Group{
    public:
        vector<string> modelsPaths;
        vector<VBO> vbos;
        Group();
        Group(vector<VBO> vbos);
        Group(vector<string> modelsPaths);
};

class Projection{
    public:
        float fov;
        float near;
        float far;
        Projection();
        Projection(float newFov, float newNear, float newFar);
};

class Camera{
    public:
        Point position;
        Point lookAt;
        Point up; 
        Projection projection;
        Camera();
        Camera(Point newPosition, Point newLookAt, Point newUp, Projection newProjection);
        Camera(XMLElement *cameraElement);
};

class World{
    public:
        Window window;
        Camera camera;
        Group group;
        World();
        World(Window newWindow, Camera newCamera, Group newGroup);
        World(char *path);
        void loadGroup();
};

#endif