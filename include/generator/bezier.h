#ifndef __BEZIER__
#define __BEZIER__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../point.h"
#include "../triangle.h"

using namespace std;

pair<vector<Point>, vector<Triangle> > generateBezier(char *path, int level);

#endif