#include "../../../include/generator/sphere.h"

pair<vector<Point>, vector<Triangle>> generateSphere(float radius, int slices, int stacks) {
    vector<Triangle> triangles;
    vector<Point> vertices;

    const float angleIncrementStacks = M_PI / stacks;
    const float angleIncrementSlices = (2 * M_PI) / slices;

    for (int i = 0; i < slices; ++i) {
        Point baseCenterPoint(0, -radius, 0);
        vertices.push_back(baseCenterPoint);

        Triangle baseTriangle(i * (2 * stacks), i * (2 * stacks) + 2, i * (2 * stacks) + 1);
        triangles.push_back(baseTriangle);

        for (int j = 1; j < stacks; ++j) {
            float	angleStack = j * angleIncrementStacks;
            float	angleSlice = i * angleIncrementSlices;

            Point p1(radius * cos(angleStack - M_PI_2) * sin(angleSlice),
                     radius * sin(angleStack - M_PI_2),
                     radius * cos(angleStack - M_PI_2) * cos(angleSlice));
            Point p2(radius * cos(angleStack - M_PI_2) * sin((i + 1) * angleIncrementSlices),
                     radius * sin(angleStack - M_PI_2),
                     radius * cos(angleStack - M_PI_2) * cos((i + 1) * angleIncrementSlices));
            vertices.push_back(p1);
            vertices.push_back(p2);

            if (j != stacks - 1) {
                Triangle t1(i * (2 * stacks) + j * 2 - 1,
                            i * (2 * stacks) + j * 2,
                            i * (2 * stacks) + j * 2 + 1);
                Triangle t2(i * (2 * stacks) + j * 2,
                            i * (2 * stacks) + j * 2 + 2,
                            i * (2 * stacks) + j * 2 + 1);
                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }

        Point topCenterPoint(0, radius, 0);
        vertices.push_back(topCenterPoint);

        Triangle topTriangle(i * (2 * stacks) + stacks * 2 - 3,
                             i * (2 * stacks) + stacks * 2 - 2,
                             i * (2 * stacks) + stacks * 2 - 1);
        triangles.push_back(topTriangle);
    }

    return make_pair(vertices, triangles);
}
