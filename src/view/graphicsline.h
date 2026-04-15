#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include <QGraphicsLineItem>
#include "../core/core.h"
#include "graphicsobject.h"

class GraphicsLine : public QGraphicsLineItem, public GraphicsObject {
private:
    Line* m_model;

public:
    GraphicsLine(Line* l) : m_model(l) {
        setPen(QPen(Qt::black, 2));
    }

    void attach() override {
        m_model->addObserver(this);
        sync();
    }

    Line* model() override {
        return m_model;
    }

    void sync() {
        setLine(m_model->x1(), m_model->y1(), m_model->x2(), m_model->y2());
    }
};

#endif // GRAPHICSLINE_H
