#include "../../include/plane.h"

Model generatePlane(float length, int divisions){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = length/2.0;
    float initialZ = length/2.0;

    float x = initialX;
    float z = initialZ;

    for(int i = 0; i < divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j < divisions; j++){
            x = initialX - j*squareLength;

            Point p1 = Point(x, 0, z);
            Point p2 = Point(x, 0, z-squareLength);
            Point p3 = Point(x-squareLength, 0, z-squareLength);
            Point p4 = Point(x-squareLength, 0, z);

            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p4);

            Triangle t1 = Triangle(i*4*divisions + 4*j, i*4*divisions + 4*j + 1, i*4*divisions + 4*j + 2);
            Triangle t2 = Triangle(i*4*divisions + 4*j, i*4*divisions + 4*j + 2, i*4*divisions + 4*j + 3);

            triangles.push_back(t1);
            triangles.push_back(t2);
        }
    }

    return Model(vertices, triangles);
}