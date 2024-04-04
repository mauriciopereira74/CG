#ifndef __ELLIPSOID__
#define __ELLIPSOID__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateEllipsoid(float a, float b, float c, int slices, int stacks);

#endif