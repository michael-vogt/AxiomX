#ifndef POINT_H
#define POINT_H

#include "geoobject.h"

class Point : public GeoObject {
protected:
    double m_x, m_y;

public:
    Point(double x, double y) : m_x(x), m_y(y) {}

    double x() {
        return m_x;
    }

    double y() {
        return m_y;
    }

    void set(double nx, double ny) {
        m_x = nx;
        m_y = ny;
        notify();
    }

    void update() {
        // free point -> nothing to do
    }
};

#endif // POINT_H
