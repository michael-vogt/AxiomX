#ifndef GRAPHICSPOINT_H
#define GRAPHICSPOINT_H

#include <QGraphicsEllipseItem>
#include "point.h"
#include "observer.h"
#include "graphicsobject.h"

namespace View {
class GraphicsPoint;
}

class GraphicsPoint : public QGraphicsEllipseItem, public GraphicsObject {
private:
    Point* model;
    bool updating = false;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && !updating) {
            QPointF newPos = value.toPointF();
            model->set(newPos.x(), newPos.y());
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

public:
    GraphicsPoint(Point* p) : QGraphicsEllipseItem(-5, -5, 10, 10), model(p) {
        setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setBrush(Qt::blue);

        //model->addObserver(this);
        //sync();
    }

    void attach() override {
        model->addObserver(this);
        sync();
    }

    Point* getModel() override {
        return model;
    }

    void sync() override {
        updating = true;
        setPos(model->getX(), model->getY());
        updating = false;
    }
};

#endif // GRAPHICSPOINT_H
