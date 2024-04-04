#ifndef __BOX__
#define __BOX__

#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateBox(float length, int divisions);

#endif