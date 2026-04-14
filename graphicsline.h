#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include <QGraphicsLineItem>
#include "line.h"
#include "graphicsobject.h"

namespace View {
class GraphicsLine;
}

class GraphicsLine : public QGraphicsLineItem, public GraphicsObject {
private:
    Line* model;

public:
    GraphicsLine(Line* l) : model(l) {
        setPen(QPen(Qt::black, 2));
    }

    void attach() override {
        model->addObserver(this);
        sync();
    }

    Line* getModel() override {
        return model;
    }

    void sync() {
        setLine(model->getX1(), model->getY1(), model->getX2(), model->getY2());
    }
};

#endif // GRAPHICSLINE_H
