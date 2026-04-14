#ifndef POINTONLINE_H
#define POINTONLINE_H

#include "point.h"
#include "line.h"

namespace Core {
class PointOnLine;
}

class PointOnLine : public Point {
protected:
    Line* l;

public:
    PointOnLine(Line* l) {
        this->p = p;
        this->l = l;
    }
};

#endif // POINTONLINE_H
