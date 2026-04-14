#ifndef LINE_H
#define LINE_H

namespace Core {
class Line;
}

#include "geoobject.h"

class Line : public GeoObject
{
protected:
    Point* p1;
    Point* p2;

    // cached for view
    double x1, x2, y1, y2;

public:
    Line(Point* a, Point* b) : p1(a), p2(b) {
        p1->addDependent(this);
        p2->addDependent(this);
        update();
    }

    Point* getP1() {
        return p1;
    }

    Point* getP2() {
        return p2;
    }

    double getX1() {
        return x1;
    }

    double getX2() {
        return x2;
    }

    double getY1() {
        return y1;
    }

    double getY2() {
        return y2;
    }

    void update() override {
        x1 = p1->getX();
        y1 = p1->getY();
        x2 = p2->getX();
        y2 = p2->getY();
    }

};

#endif // LINE_H
