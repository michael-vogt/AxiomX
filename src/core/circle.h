#ifndef CIRCLE_H
#define CIRCLE_H

#include "geoobject.h"
#include "line.h"
#include "point.h"

class Circle : public GeoObject {
private:
    void updateCircle();
protected:
    Point* m_center;
    Point* m_pointOnCircle;
    double m_radius;

    double m_x1, m_y1, m_x2, m_y2;

public:
    Circle(Point* center, Point* pointOnCircle);

    double radius();

    double x1();

    double y1();

    bool pointOnCircle(const QPointF& p, double delta = 0.0);

    std::vector<Point*> intersect(Circle* other);

    std::vector<Point*> intersect(Line* other, LineType lineType);

    void update() override;
};


#endif // CIRCLE_H
