#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "observer.h"
#include "geoobject.h"

namespace View {
class GraphicsObject;
}

class GraphicsObject : public Observer {
public:
    virtual void attach() = 0;
    virtual GeoObject* model() = 0;
};

#endif // GRAPHICSOBJECT_H
