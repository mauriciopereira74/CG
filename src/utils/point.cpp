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

// Adicione esta definição de construtor à classe Point
Point::Point(XMLElement *elem) {
    if (elem) {
        const char* xAttr = elem->Attribute("x");
        const char* yAttr = elem->Attribute("y");
        const char* zAttr = elem->Attribute("z");
        
        if (xAttr && yAttr && zAttr) {
            x = atof(xAttr);
            y = atof(yAttr);
            z = atof(zAttr);
        }
    }
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

float Point::distanceTo(Point p) {
    float dx = p.x - x;
    float dy = p.y - y;
    float dz = p.z - z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}