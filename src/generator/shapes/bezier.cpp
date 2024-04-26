#include "../../../include/generator/bezier.h"


void computeMatrix(Point points[4][4], Point res[4][4]){
    float M[4][4] = {
        {-1, 3, -3, 1}, 
        {3, -6, 3, 0}, 
        {-3, 3, 0, 0}, 
        {1, 0, 0, 0}
    };

    Point aux[4][4];
    for (int i=0; i<4; i++) {
        for (int j=0; j < 4; j++) {
            aux[i][j].x = 0.0f;
            aux[i][j].y = 0.0f;
            aux[i][j].z = 0.0f;
            for (int k=0; k<4; k++) {
                aux[i][j].x += M[i][k] * points[k][j].x;                
                aux[i][j].y += M[i][k] * points[k][j].y;
                aux[i][j].z += M[i][k] * points[k][j].z;
            }
        }
    }

    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j].x = 0.0f;
            res[i][j].y = 0.0f;
            res[i][j].z = 0.0f;
            for (int k=0; k<4; k++) {
                res[i][j].x += aux[i][k].x * M[k][j];
                res[i][j].y += aux[i][k].y * M[k][j];
                res[i][j].z += aux[i][k].z * M[k][j];
            }
        }
    }
}


Point patchPoint(float u, float v, Point M[4][4]){
    float U[4] = {(float)pow(u, 3), (float)pow(u, 2), u, 1};
    float V[4] = {(float)pow(v, 3), (float)pow(v, 2), v, 1};

    Point res[4];
    for(int i=0; i<4; i++){
        res[i].x = 0.0f;
        res[i].y = 0.0f;
        res[i].z = 0.0f;
        for(int j=0; j<4; j++){
            res[i].x += U[j] * M[j][i].x;
            res[i].y += U[j] * M[j][i].y;
            res[i].z += U[j] * M[j][i].z;
        }
    }

    Point p;
    p.x = res[0].x * V[0] + res[1].x * V[1] + res[2].x * V[2] + res[3].x * V[3];
    p.y = res[0].y * V[0] + res[1].y * V[1] + res[2].y * V[2] + res[3].y * V[3];
    p.z = res[0].z * V[0] + res[1].z * V[1] + res[2].z * V[2] + res[3].z * V[3];

    return p;
}


Point(*readFile(char *path, int *n))[4][4]{
    ifstream file(path);

    if(!file.is_open()){
        cout << "Wrong path!" << endl;
        exit(1);
    }

    string line;
    string nPatchesStr;
    string nPointsStr;

    getline(file, line);
    stringstream stream(line);
    stream >> nPatchesStr;

    int nPatches = stoi(nPatchesStr);
    int **indexes = new int*[nPatches];
    for(int i=0; i<nPatches; i++){
        getline(file, line);
        stringstream stream(line);
        string token;

        indexes[i] = new int[16];
        for(int j=0; j<16; j++) {
            getline(stream, token, ',');
            indexes[i][j] = stoi(token);
        }
    }

    getline(file, line);
    stream = stringstream(line);
    stream >> nPointsStr;

    int nPoints = stoi(nPointsStr);
    Point *points = new Point[nPoints];
    for(int i=0; i<nPoints; i++){
        getline(file, line);
        stringstream stream(line);
        string x, y, z;
        stream >> x >> y >> z;

        points[i] = Point(stof(x), stof(y), stof(z));
    }

    Point (*patches)[4][4] = new Point[nPatches][4][4];
    for(int i=0; i<nPatches; i++){
        for(int j=0; j<16; j++){
            patches[i][j/4][j%4] = points[indexes[i][j]];
        }
    }

    *n = nPatches;

    return patches;
}


pair<vector<Point>, vector<Triangle> > generateBezier(char *path, int level){
    vector<Point> vertices;
    vector<Triangle> triangles;
    int n;
    Point (*patches)[4][4] = readFile(path, &n);
    float step = 1 / (float)level;
    int nPoints = (float)pow(level+1, 2); //N ª pontos num patch

    int index = 0;
    for(int i=0; i<n; i++){
        Point res[4][4];
        computeMatrix(patches[i], res);

        for(int u=0; u < level; u++){
            for(int v=0; v <= level; v++){  
                vertices.push_back(patchPoint(u*step, v*step, res));
                vertices.push_back(patchPoint((u+1)*step, v*step, res));

                if(v != level){
                    triangles.push_back(Triangle(index, index+2, index+1));
                    triangles.push_back(Triangle(index+1, index+2, index+3));
                }
                index+=2;
            }
        }
    }

    delete[] patches;

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}