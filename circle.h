#ifndef CIRCLE_H
#define CIRCLE_H

#include "geoobject.h"

namespace Core {
class Circle;
}

class Circle : public GeoObject {
protected:
    Point* center;
    double radius;

public:
    Circle(Point* center, double radius) {
        this->center = center;
        this->radius = radius;
        this->dependents.push_back(center);
    }

    Point* getCenter() {
        return this->center;
    }

    double getRadius() {
        return this->radius;
    }

    void update() override {
        // currently does nothing
    }
};


#endif // CIRCLE_H
