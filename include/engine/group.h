#ifndef __GROUP__
#define __GROUP__

#include <vector>
#include <string.h>
#include "model.h"
#include "transformation.h"
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Group{
    public:
        vector<Group> groups;
        vector<Model> models;
        vector<Transformation *> transforms;
        Point *color;

        Group();
        Group(XMLElement *groupElement);
        Group(pair<vector<float>, vector<int> > vectors, float radiusIn, float radiusOut, float verticalAngle, Point *color);
        void loadModels();
        void drawModels();
};

#endif