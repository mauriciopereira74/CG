#ifndef __CYLINDER__
#define __CYLINDER__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateCylinder(float radius, float height, int slices);

#endif