#include "../../../include/generator/cone.h"

pair<vector<Point>, vector<Triangle>> generateCone(float radius, float height, int slices, int stacks) {
    vector<Point> points;
    vector<Triangle> triangles;

    const float angleIncrement = (2 * M_PI) / slices;
    const float heightStep = height / stacks;
    const float radiusStep = radius / stacks;

    for (int i = 0; i < slices; ++i) {
        // Adicionando o ponto central
        Point centralPoint(0, 0, 0);
        points.push_back(centralPoint);

        // Triângulo da base
        Triangle baseTriangle(i * (2 * stacks + 2) + 2, i * (2 * stacks + 2) + 1, i * (2 * stacks + 2));
        triangles.push_back(baseTriangle);

        for (int j = 0; j < stacks; ++j) {
            // Calculando o raio e a altura para este nível
            float currentRadius = radius - j * radiusStep;
            float currentHeight = j * heightStep;

            // Calculando os pontos para este nível
            Point p1(currentRadius * sin(i * angleIncrement), currentHeight, currentRadius * cos(i * angleIncrement));
            Point p2(currentRadius * sin((i + 1) * angleIncrement), currentHeight, currentRadius * cos((i + 1) * angleIncrement));
            points.push_back(p1);
            points.push_back(p2);

            if (j != stacks - 1) {
                // Adicionando os triângulos para conectar os pontos neste nível
                Triangle t1(points.size() - 2, points.size() - 1, points.size() - 3);
                Triangle t2(points.size() - 1, points.size() - 4, points.size() - 3);
                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }

        // Adicionando o ponto do topo
        Point topPoint(0, height, 0);
        points.push_back(topPoint);

        // Triângulo do topo
        Triangle topTriangle(i * (2 * stacks + 2) + stacks * 2 - 1, i * (2 * stacks + 2) + stacks * 2, i * (2 * stacks + 2) + stacks * 2 + 1);
        triangles.push_back(topTriangle);
    }

    return make_pair(points, triangles);
}
