#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QGraphicsScene>
//#include "../core/core.h"
#include "../core/geoobject.h"
#include "observer.h"
//#include "../control/scenecontroller.h"

class GraphicsObject : public Observer {
protected:
    bool m_selected = false;
    QGraphicsScene* m_scene = nullptr;


public:
    bool selected();
    QGraphicsScene* scene();
    void setScene(QGraphicsScene* s);
    virtual void attach() = 0;
    virtual GeoObject* model() = 0;
    virtual void setSelectedVisual(bool selected) = 0;
};

#endif // GRAPHICSOBJECT_H
