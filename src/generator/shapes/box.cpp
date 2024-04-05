#include "../../../include/generator/box.h"

pair<vector<Point>, vector<Triangle>> generateXZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible) {
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length / divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float z = initialZ;

    for (int i = 0; i < divisions; i++) {
        x = initialX;
        z = initialZ - i * squareLength;

        for (int j = 0; j < divisions; j++) {
            x = initialX - j * squareLength;

            Point p1 = Point(x, initialY, z);
            Point p2 = Point(x, initialY, z - squareLength);
            Point p3 = Point(x - squareLength, initialY, z - squareLength);
            Point p4 = Point(x - squareLength, initialY, z);

            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p4);

            Triangle t1, t2;
            if (isVisible) {
                t1 = Triangle(*index, *index + 1, *index + 2);
                t2 = Triangle(*index, *index + 2, *index + 3);
            } else {
                t1 = Triangle(*index + 1, *index, *index + 2);
                t2 = Triangle(*index + 2, *index, *index + 3);
            }

            triangles.push_back(t1);
            triangles.push_back(t2);

            *index += 4; // Incrementa o índice para os próximos vértices
        }
    }

    return pair<vector<Point>, vector<Triangle>>(vertices, triangles);
}

pair<vector<Point>, vector<Triangle>> generateYZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible) {
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length / divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float y = initialY;
    float z = initialZ;

    for (int i = 0; i < divisions; i++) {
        z = initialZ;
        y = initialY - i * squareLength;

        for (int j = 0; j < divisions; j++) {
            z = initialZ - j * squareLength;

            Point p1 = Point(initialX, y, z);
            Point p2 = Point(initialX, y, z - squareLength);
            Point p3 = Point(initialX, y - squareLength, z - squareLength);
            Point p4 = Point(initialX, y - squareLength, z);

            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p4);

            Triangle t1, t2;
            if (isVisible) {
                t1 = Triangle(*index + 1, *index, *index + 2);
                t2 = Triangle(*index, *index + 2, *index + 3);
            } else {
                t1 = Triangle(*index, *index + 1, *index + 2);
                t2 = Triangle(*index, *index + 2, *index + 3);
            }

            triangles.push_back(t1);
            triangles.push_back(t2);

            *index += 4; // Incrementa o índice para os próximos vértices
        }
    }

    return pair<vector<Point>, vector<Triangle>>(vertices, triangles);
}

pair<vector<Point>, vector<Triangle>> generateXYplane(Point initialPoint, float length, int divisions, int *index, bool isVisible) {
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length / divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float y = initialY;

    for (int i = 0; i < divisions; i++) {
        y = initialY;
        x = initialX + i * squareLength;

        for (int j = 0; j < divisions; j++) {
            y = initialY + j * squareLength;

            Point p1 = Point(x, y, initialZ);
            Point p2 = Point(x, y + squareLength, initialZ);
            Point p3 = Point(x + squareLength, y + squareLength, initialZ);
            Point p4 = Point(x + squareLength, y, initialZ);

            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p4);

            Triangle t1, t2;
            if (isVisible) {
                t1 = Triangle(*index + 1, *index, *index + 2);
                t2 = Triangle(*index, *index + 2, *index + 3);
            } else {
                t1 = Triangle(*index, *index + 1, *index + 2);
                t2 = Triangle(*index, *index + 2, *index + 3);
            }

            triangles.push_back(t1);
            triangles.push_back(t2);
            
            *index += 4; // Incrementa o índice para os próximos vértices
        }
    }

    return pair<vector<Point>, vector<Triangle>>(vertices, triangles);
}



pair<vector<Point>, vector<Triangle>> generateBox(float size, int divisions) {
    vector<Point> verts;
    vector<Triangle> tris;
    int idx = 0;
    float half_size = size / 2;

    pair<vector<Point>, vector<Triangle>> plane1_xz = generateXZplane(Point(half_size, half_size, half_size), size, divisions, &idx, true);
    pair<vector<Point>, vector<Triangle>> plane1_yz = generateYZplane(Point(half_size, half_size, half_size), size, divisions, &idx, true);
    pair<vector<Point>, vector<Triangle>> plane1_xy = generateXYplane(Point(-half_size, -half_size, half_size), size, divisions, &idx, true);
    pair<vector<Point>, vector<Triangle>> plane2_xz = generateXZplane(Point(half_size, -half_size, half_size), size, divisions, &idx, false);
    pair<vector<Point>, vector<Triangle>> plane2_yz = generateYZplane(Point(-half_size, half_size, half_size), size, divisions, &idx, false);
    pair<vector<Point>, vector<Triangle>> plane2_xy = generateXYplane(Point(-half_size, -half_size, -half_size), size, divisions, &idx, false);

    verts.insert(verts.end(), plane1_xz.first.begin(), plane1_xz.first.end());
    verts.insert(verts.end(), plane2_xz.first.begin(), plane2_xz.first.end());
    verts.insert(verts.end(), plane1_yz.first.begin(), plane1_yz.first.end());
    verts.insert(verts.end(), plane2_yz.first.begin(), plane2_yz.first.end());
    verts.insert(verts.end(), plane1_xy.first.begin(), plane1_xy.first.end());
    verts.insert(verts.end(), plane2_xy.first.begin(), plane2_xy.first.end());

    tris.insert(tris.end(), plane1_xz.second.begin(), plane1_xz.second.end());
    tris.insert(tris.end(), plane2_xz.second.begin(), plane2_xz.second.end());
    tris.insert(tris.end(), plane1_yz.second.begin(), plane1_yz.second.end());
    tris.insert(tris.end(), plane2_yz.second.begin(), plane2_yz.second.end());
    tris.insert(tris.end(), plane1_xy.second.begin(), plane1_xy.second.end());
    tris.insert(tris.end(), plane2_xy.second.begin(), plane2_xy.second.end());

    return make_pair(verts, tris);
}
