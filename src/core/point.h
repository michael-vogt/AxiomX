#ifndef POINT_H
#define POINT_H

#include "geoobject.h"

class Point : public GeoObject {
protected:
    double m_x, m_y;
    int m_id;

public:
    Point(double x, double y);

    int id();

    void setId(int id);

    double x();

    double y();

    void set(double nx, double ny);

    void update() override;
};

#endif // POINT_H
