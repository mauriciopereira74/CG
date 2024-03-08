#ifndef __VBO__
#define __VBO__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class VBO { 
    public:
        int nVertices;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;
        VBO(char* path);
        void draw();
};

#endif