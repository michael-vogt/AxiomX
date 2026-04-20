#ifndef CIRCLE_H
#define CIRCLE_H

#include "geoobject.h"
#include "point.h"
#include "line.h"
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

    bool pointOnCircle(const QPointF& p, double delta = 0.0) {
        QPointF m(m_x1, m_y1);
        QLineF mp(m, p);
        return (std::abs(mp.length() - m_radius) <= delta);
    }

    std::vector<Point*> intersect(Circle* other) {
        std::vector<Point*> points;

        double r1 = m_radius;
        double r2 = other->radius();
        double dx = other->x1() - m_x1;
        double dy = other->y1() - m_y1;

        double d = std::sqrt(dx*dx + dy*dy);

        if (d > r1 + r2 || d < std::abs(r1 - r2)) { // keine Lösung
            return points;
        }

        double a = (r1*r1 - r2*r2 + d*d) / (2*d);
        double h = std::sqrt(r1*r1 - a*a);

        double x3 = m_x1 + a * dx / d;
        double y3 = m_y1 + a * dy / d;

        Point* sp1 = new Point(x3 + h * dy / d, y3 - h * dx / d);
        Point* sp2 = new Point(x3 - h * dy / d, y3 + h * dx / d);

        points.push_back(sp1);
        if (!(std::abs(h) < 1e-10)) {
            points.push_back(sp2);
        }

        return points;
    }

    std::vector<Point*> intersect(Line* other, LineType lineType) {
        std::vector<Point*> points;

        double dx = other->x2() - other->x1();
        double dy = other->y2() - other->y1();

        double A = dx*dx + dy*dy;
        double B = 2 * (dx * (other->x1() - m_x1) + dy * (other->y1() - m_y1));
        double C = (other->x1() - m_x1) * (other->x1() - m_x1) + (other->y1() - m_y1) * (other->y1() - m_y1) - m_radius * m_radius;

        double D = B*B - 4*A*C;

        if (D >= 0) {
            double t1 = (-B - std::sqrt(D)) / (2*A);
            double x = other->x1() + t1 * dx;
            double y = other->y1() + t1 * dy;
            if (t1 < 0) {
                if (lineType == LINE) points.push_back(new Point(x, y));
            } else if (t1 > 1) {
                if (lineType != SEGMENT) points.push_back(new Point(x, y));
            } else {
                points.push_back(new Point(x, y));
            }

            if (std::abs(D) > 1e-10) {
                double t2 = (-B + std::sqrt(D)) / (2*A);
                x = other->x1() + t2 * dx;
                y = other->y1() + t2 * dy;
                if (t2 < 0) {
                    if (lineType == LINE) points.push_back(new Point(x, y));
                } else if (t2 > 1) {
                    if (lineType != SEGMENT) points.push_back(new Point(x, y));
                } else {
                    points.push_back(new Point(x, y));
                }
            }
        }

        return points;
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
