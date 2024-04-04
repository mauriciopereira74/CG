#include "../../../include/generator/cylinder.h"

pair<vector<Point>, vector<Triangle> > generateCylinder(float radius, float height, int slices) {
    vector<Point> points;
    vector<Triangle> triangles;

    float h_2 = height / 2.0;
    float alpha = (2 * M_PI) / slices;

    for(int i = 0; i < slices; i++){
        Point topPoint = Point(0, h_2, 0);
        Point p1 = Point(radius * sin(i*alpha), h_2, radius * cos(i*alpha));
        Point p2 = Point(radius * sin((i+1)*alpha), h_2, radius * cos((i+1)*alpha));
        Point p3 = Point(radius * sin(i*alpha), -h_2, radius * cos(i*alpha));
        Point p4 = Point(radius * sin((i+1)*alpha), -h_2, radius * cos((i+1)*alpha));
        Point bottomPoint = Point(0, -h_2, 0);
        
        points.push_back(topPoint);
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p4);
        points.push_back(bottomPoint);

        Triangle topTriangle = Triangle(i*6, i*6 + 1, i*6 + 2);
        Triangle t1 = Triangle(i*6 + 1, i*6 + 4, i*6 + 2);
        Triangle t2 = Triangle(i*6 + 1, i*6 + 3, i*6 + 4);
        Triangle bottomTriangle = Triangle(i*6 + 3, i*6 + 5, i*6 + 4);

        triangles.push_back(topTriangle);
        triangles.push_back(t1);
        triangles.push_back(t2);
        triangles.push_back(bottomTriangle);
	}

    return pair<vector<Point>, vector<Triangle> >(points, triangles);
}