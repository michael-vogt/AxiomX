#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "../core/core.h"
#include "observer.h"

class GraphicsObject : public Observer {
public:
    virtual void attach() = 0;
    virtual GeoObject* model() = 0;
    virtual void setSelectedVisual(bool selected) = 0;
};

#endif // GRAPHICSOBJECT_H
