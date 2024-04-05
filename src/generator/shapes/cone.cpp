#include "../../../include/generator/cone.h"

pair<vector<Point>, vector<Triangle> > generateCone(float radius, float height, int slices, int stacks){
    vector<Point> points;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float hPart = height / stacks;
    float rPart = radius / stacks;

    for(int i = 0; i < slices; i++){
        Point centralPoint = Point(0, 0, 0);
        points.push_back(centralPoint);

        Triangle baseTriangle = Triangle(i*(2*stacks+2) + 2, i*(2*stacks+2) + 1, i*(2*stacks+2));
        triangles.push_back(baseTriangle);

        for(int j = 0; j < stacks; j++){
            Point p1 = Point((radius - j*rPart) * sin(i*alpha), j*hPart, (radius - j*rPart) * cos(i*alpha));
            Point p2 = Point((radius - j*rPart) * sin((i+1)*alpha), j*hPart, (radius - j*rPart) * cos((i+1)*alpha));
            points.push_back(p1);
            points.push_back(p2);

            if(j!=stacks-1){
                Triangle t1 = Triangle(i*(2*stacks+2)+j*2+1, i*(2*stacks+2)+j*2+2, i*(2*stacks+2)+j*2+3);
                Triangle t2 = Triangle(i*(2*stacks+2)+j*2+2, i*(2*stacks+2)+j*2+4, i*(2*stacks+2)+j*2+3);
                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }

        Point topPoint = Point(0, height, 0);
        points.push_back(topPoint);

        Triangle topTriangle = Triangle(i*(2*stacks+2)+stacks*2 - 1, i*(2*stacks+2)+stacks*2, i*(2*stacks+2)+stacks*2 + 1);
        triangles.push_back(topTriangle);
    }

    return pair<vector<Point>, vector<Triangle> >(points, triangles);
}