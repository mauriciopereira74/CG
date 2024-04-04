#ifndef __SPHERE__
#define __SPHERE__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateSphere(float radius, int slices, int stacks);

#endif