#ifndef __CONE__
#define __CONE__

#include <math.h>
#include <vector>
#include "point.h"
#include "triangle.h"
#include "model.h"

using namespace std;

Model generateCone(float radius, float height, int slices, int stacks);

#endif