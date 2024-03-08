#include "../../include/model.h"

Model::Model(vector<Point> newVertices, vector<Triangle> newTriangles){
    vertices = newVertices;
    triangles = newTriangles;
}

void Model::toFile(char* path){
    ofstream file; 
    file.open(path);
    char buffer[1024];
    
    int nVertices = vertices.size(), nTriangles = triangles.size();

    //First line (nVertices e nTriangles)
    file << nVertices << " " << nTriangles << "\n";

    //Vertices
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
        file << buffer;
    }

    //Triangles
    for(int i = 0; i < nTriangles; i++){
        sprintf(buffer, "%d %d %d\n", triangles[i].indP1, triangles[i].indP2, triangles[i].indP3);
        file << buffer;
    }

    file.close();
}
