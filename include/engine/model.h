#ifndef __MODEL__
#define __MODEL__

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../point.h"
#include "../tinyxml2/tinyxml2.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace tinyxml2;
using namespace std;

class Model{
    public:
        vector<float> points;
        vector<int> indexes;
        Point *color;

        int nVertices;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;        

        Model();
        Model(XMLElement *elem);
        Model(vector<float> points, vector<int> indexes);
        void load();
        void draw();
        static pair<vector<float>, vector<int> > readFile(char *path);
};

#endif
