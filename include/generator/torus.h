#ifndef __TORUS__
#define __TORUS__

#include <vector>
#include <math.h>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateTorus(float radiusIn, float radiusOut, int slices, int layers);

#endif
