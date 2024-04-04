#ifndef __CONE__
#define __CONE__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateCone(float radius, float height, int slices, int stacks);

#endif