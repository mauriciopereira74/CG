#include "../../../include/generator/sphere.h"

pair<vector<Point>, vector<Triangle> > generateSphere(float radius, int slices, int stacks){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    for(int i = 0; i < slices; i++){
        //Ponto superior
        Point centralBottomPoint = Point(0, -radius, 0);
        vertices.push_back(centralBottomPoint);   

        Triangle baseTriangle = Triangle(i*(2*stacks), i*(2*stacks) + 2, i*(2*stacks) + 1);
        triangles.push_back(baseTriangle);

        for(int j = 1; j < stacks; j++){
            Point p1 = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));
            Point p2 = Point(radius * cos(j*beta-M_PI_2) * sin((i+1)*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos((i+1)*alpha));
            vertices.push_back(p1);
            vertices.push_back(p2);
            
            if(j!=stacks-1){
                Triangle t1 = Triangle(i*(2*stacks) + j*2 - 1, i*(2*stacks) + j*2, i*(2*stacks) + j*2 + 1);
                Triangle t2 = Triangle(i*(2*stacks) + j*2, i*(2*stacks) + j*2 + 2, i*(2*stacks) + j*2 + 1);

                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }

        //Ponto superior
        Point topCentralPoint = Point(0, radius, 0);
        vertices.push_back(topCentralPoint);

        Triangle topTriangle = Triangle(i*(2*stacks) + stacks*2 - 3, i*(2*stacks) + stacks*2 - 2, i*(2*stacks) + stacks*2 - 1);
        triangles.push_back(topTriangle);
    }

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}