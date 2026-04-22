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
    Circle(Point* center, Point* pointOnCircle);

    Point* center();

    double radius();

    double x1();

    double x2();

    double y1();

    double y2();

    bool pointOnCircle(const QPointF& p, double delta = 0.0);

    std::vector<Point*> intersect(Circle* other);

    std::vector<Point*> intersect(Line* other, LineType lineType);

    void update() override;
};


#endif // CIRCLE_H
