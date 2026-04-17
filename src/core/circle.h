#ifndef CIRCLE_H
#define CIRCLE_H

#include "geoobject.h"
#include "point.h"
#include <QLineF>

class Circle : public GeoObject {
protected:
    Point* m_center;
    Point* m_pointOnCircle;
    double m_radius;

    double m_x1, m_y1, m_x2, m_y2;

public:
    Circle(Point* center, Point* pointOnCircle) : m_center(center), m_pointOnCircle(pointOnCircle) {
        QPointF p1(center->x(), center->y());
        QPointF p2(pointOnCircle->x(), pointOnCircle->y());
        m_radius = QLineF(p1, p2).length();
        m_center->addDependent(this);
        m_pointOnCircle->addDependent(this);
        update();
    }

    Point* center() {
        return m_center;
    }

    double radius() {
        return m_radius;
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
        m_x1 = m_center->x();
        m_y1 = m_center->y();
        m_x2 = m_pointOnCircle->x();
        m_y2 = m_pointOnCircle->y();

        QPointF p1(m_center->x(), m_center->y());
        QPointF p2(m_pointOnCircle->x(), m_pointOnCircle->y());
        m_radius = QLineF(p1, p2).length();
    }
};


#endif // CIRCLE_H
