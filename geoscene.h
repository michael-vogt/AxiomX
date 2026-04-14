#ifndef GEOSCENE_H
#define GEOSCENE_H

#include <vector>
#include "core.h"

namespace View {
class GeoScene;
}

class GeoScene {
private:
    std::vector<GeoObject*> objects;
    std::vector<Point*> points;
    std::vector<Line*> lines;

public:
    void add(Point* p) {
        points.push_back(p);
        objects.push_back(p);
    }

    void add(Line* l) {
        lines.push_back(l);
        objects.push_back(l);
    }
};

#endif // GEOSCENE_H
