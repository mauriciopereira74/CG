#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "../include/point.h"
#include "../include/plane.h"
#include "../include/box.h"
#include "../include/cone.h"
#include "../include/sphere.h"

using namespace std;

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
    
    if (regex_match(inp, regex(erPlane))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char *filePath = argv[4];
        Model plane = generatePlane(length, divisions);
        
        plane.toFile(filePath);
    }
    else if(regex_match(inp, regex(erBox))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        char *filePath = argv[4];
        Model box = generateBox(length, divisions);

        box.toFile(filePath);
    }
    else if(regex_match(inp, regex(erCone))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filePath = argv[6];
        Model cone = generateCone(radius, height, slices, stacks);

        cone.toFile(filePath);
    }
    else if(regex_match(inp, regex(erSphere))){
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        char *filePath = argv[5];
        Model sphere = generateSphere(radius, slices, stacks);

        sphere.toFile(filePath);
    }
    else cout << "Invalid input!" << endl;

    return 0;
}