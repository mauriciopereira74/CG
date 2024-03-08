#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "point.h"
#include "triangle.h"

using namespace std;

class Model{
    public:
        vector<Point> vertices;
        vector<Triangle> triangles;

        Model(vector<Point> vertices, vector<Triangle> triangles);
        void toFile(char* path);
};

#endif
