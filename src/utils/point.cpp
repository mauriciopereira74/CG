#include "../../include/point.h"

Point::Point(){
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float x1, float y1, float z1){
    x = x1;
    y = y1;
    z = z1;
}

void Point::normalizeVector(){
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    x = x / vectorLength;
    y = y / vectorLength;
    z = z / vectorLength;
}

void Point::crossProduct(Point v){
    float xAux = x, yAux = y, zAux = z;
    x = yAux * v.z - zAux * v.y;
    y = zAux * v.x - xAux * v.z; 
    z = xAux * v.y - yAux * v.x;
}
