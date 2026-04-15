#ifndef LINE_H
#define LINE_H

#include "geoobject.h"
#include "point.h"

class Line : public GeoObject
{
protected:
    Point* m_p1;
    Point* m_p2;

    // cached for view
    double m_x1, m_x2, m_y1, m_y2;

public:
    Line(Point* a, Point* b) : m_p1(a), m_p2(b) {
        m_p1->addDependent(this);
        m_p2->addDependent(this);
        update();
    }

    Point* p1() {
        return m_p1;
    }

    Point* p2() {
        return m_p2;
    }

    double x1() {
        return m_x1;
    }

    double x2() {
        return m_x2;
    }

    double y1() {
        return m_y1;
    }

    double y2() {
        return m_y2;
    }

    void update() override {
        m_x1 = m_p1->x();
        m_y1 = m_p1->y();
        m_x2 = m_p2->x();
        m_y2 = m_p2->y();
    }

};

#endif // LINE_H
