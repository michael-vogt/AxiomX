#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include <QGraphicsLineItem>
#include "../core/core.h"
#include "graphicsobject.h"

class GraphicsLine : public QGraphicsLineItem, public GraphicsObject {
private:
    Line* m_model;
    bool m_hovered = false;
    bool m_selected = false;

    QPen m_normalPen = QPen(Qt::black, 2);
    QPen m_hoverPen = QPen(Qt::yellow, 2);
    QPen m_selectPen = QPen(Qt::red, 2);

    void updateVisual() {
        if (m_selected) {
            setPen(m_selectPen);
        } else if (m_hovered) {
            setPen(m_hoverPen);
        } else {
            setPen(m_normalPen);
        }
    }

public:
    GraphicsLine(Line* l) : m_model(l) {
        setZValue(0);
        updateVisual();
    }

    void setHovered(bool h) {
        m_hovered = h;
        updateVisual();
    }

    void setSelectedVisual(bool s) {
        m_selected = s;
        updateVisual();
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
