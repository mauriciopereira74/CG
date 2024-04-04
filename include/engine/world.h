#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "group.h"
#include "settings.h"
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class World{
    public:
        Window window;
        Camera camera;
        vector<Group> groups;
        
        World();
        World(Window newWindow, Camera newCamera, vector<Group> newGroup);
        World(char *path);
        void loadModels();
        void drawModels();
};

#endif