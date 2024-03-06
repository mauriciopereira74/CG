#ifndef __SPHERE__
#define __SPHERE__

#include <math.h>
#include <vector>
#include "point.h"
#include "triangle.h"
#include "model.h"

using namespace std;

Model generateSphere(float radius, int slices, int stacks);

#endif