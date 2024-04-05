#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "../../include/point.h"
#include "../../include/generator/plane.h"
#include "../../include/generator/box.h"
#include "../../include/generator/cone.h"
#include "../../include/generator/sphere.h"
#include "../../include/generator/cylinder.h"
#include "../../include/generator/torus.h"
#include "../../include/generator/ellipsoid.h"

using namespace std;

void toFile(char* filename, pair<vector<Point>, vector<Triangle> > pair){
    ofstream file;
    char path[100] = "../../../demo-scenes/models/";

    file.open(strcat(path, filename));
    char buffer[1024];
    
    int nVertices = pair.first.size(), nTriangles = pair.second.size();

    //First line (nVertices e nTriangles)
    file << nVertices << " " << nTriangles << "\n";

    //Vertices
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f %f\n", pair.first[i].x, pair.first[i].y, pair.first[i].z);
        file << buffer;
    }

    //Triangles
    for(int i = 0; i < nTriangles; i++){
        sprintf(buffer, "%d %d %d\n", pair.second[i].indP1, pair.second[i].indP2, pair.second[i].indP3);
        file << buffer;
    }

    file.close();
}

int main(int argc, char *argv[]){

    string inp;

    for (int i=1; argv[i] != NULL; i++) {
        inp.append(argv[i]);
        inp.push_back(' ');
    }
    inp.pop_back();

    char erPlane[] = "plane ([0-9]+[.])?[0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erBox[] = "box ([0-9]+[.])?[0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erCone[] = "cone ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erSphere[] = "sphere ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erTorus[] = "torus ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";

    if (regex_match(inp, regex(erPlane))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char *filename = argv[4];

        pair<vector<Point>, vector<Triangle> > plane = generatePlane(length, divisions);
        toFile(filename, plane);
    }    
    else if(regex_match(inp, regex(erCone))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filename = argv[6];

        pair<vector<Point>, vector<Triangle> > cone = generateCone(radius, height, slices, stacks);
        toFile(filename, cone);
    }
    else if(regex_match(inp, regex(erBox))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char *filename = argv[4];

        pair<vector<Point>, vector<Triangle> > box = generateBox(length, divisions);
        toFile(filename, box);
    }
    else if(regex_match(inp, regex(erCone))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filename = argv[6];

        pair<vector<Point>, vector<Triangle> > cone = generateCone(radius, height, slices, stacks);
        toFile(filename, cone);
    }
    else if(regex_match(inp, regex(erSphere))){
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        char *filename = argv[5];

        pair<vector<Point>, vector<Triangle> > sphere = generateSphere(radius, slices, stacks);
        toFile(filename, sphere);
    }
    else if(regex_match(inp, regex(erTorus))){
        float radiusIn = atof(argv[2]);
        float radiusOut = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filename = argv[6];

        pair<vector<Point>, vector<Triangle> > torus = generateTorus(radiusIn, radiusOut, slices, stacks);
        toFile(filename, torus);
    }
    else cout << "Invalid input! Please try again!" << endl;


    return 0;
}
