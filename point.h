#ifndef POINT_H
#define POINT_H

#include "geoobject.h"

namespace Core {
class Point;
}

class Point : public GeoObject {
protected:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    void set(double nx, double ny) {
        x = nx;
        y = ny;
        notify();
    }

    void update() {
        // free point -> nothing to do
    }
};

#endif // POINT_H
