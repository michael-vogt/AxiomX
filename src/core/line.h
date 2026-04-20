#ifndef LINE_H
#define LINE_H

#include <QPointF>
#include "geoobject.h"
#include "point.h"
//#include "utility.h"
//#include "../view/graphicspoint.h"

double distancePointToSegment(const QPointF& p, const QPointF& a, const QPointF& b);

class Line : public GeoObject {
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

    double distanceToPoint(const QPointF& pos) {
        /*double x0 = pos.x();
        double y0 = pos.y();

        double dX2X1 = m_x2 - m_x1;
        double dY1Y0 = m_y1 - y0;
        double dX1X0 = m_x1 - x0;
        double dY2Y1 = m_y2 - m_y1;
        double numerator = std::abs(dX2X1 * dY1Y0 - dX1X0 * dY2Y1);
        double denominator = std::sqrt(dX2X1 * dX2X1 + dY2Y1 * dY2Y1);

        return numerator / denominator;*/
        QPointF a(m_p1->x(), m_p1->y());
        QPointF b(m_p2->x(), m_p2->y());
        return distancePointToSegment(pos, a, b);
    }

};

#endif // LINE_H
