#ifndef LINE_H
#define LINE_H

#include <QPointF>
#include "geoobject.h"
#include "point.h"
#include "../core/enums.h"

class Line : public GeoObject {
private:
    void updateLine();
protected:
    Point* m_p1;
    Point* m_p2;

    // cached for view
    double m_x1, m_x2, m_y1, m_y2;

public:
    Line(Point* a, Point* b);

    Point* p1();

    Point* p2();

    double x1();

    double x2();

    double y1();

    double y2();

    bool contains(const QPointF& p, LineType lineType);

    std::vector<Point*> intersect(Line* other, LineType lineTypeOther, LineType lineTypeThis);

    void update() override;

    double distanceToPoint(const QPointF& pos, LineType lineType);

};

#endif // LINE_H
