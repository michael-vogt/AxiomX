#ifndef POINT_H
#define POINT_H

#include "geoobject.h"

class Point : public GeoObject {
protected:
    double m_x, m_y;

public:
    Point(double x, double y);

    double x();

    double y();

    void set(double nx, double ny);

    void update() override;
};

#endif // POINT_H
