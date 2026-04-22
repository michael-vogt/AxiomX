#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include <QGraphicsLineItem>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include "../core/core.h"
#include "graphicsobject.h"

class GraphicsLine : public InfiniteLineItem, public GraphicsObject {
private:
    Line* m_model;
    bool m_hovered = false;

    QPen m_normalPen = QPen(Qt::black, 2);
    QPen m_hoverPen = QPen(Qt::green, 2);
    QPen m_selectPen = QPen(Qt::red, 2);

    void updateVisual() {
        if (m_selected) {
            setPen(m_selectPen);
        } else if (m_hovered) {
            setPen(m_hoverPen);
        } else {
            setPen(m_normalPen);
        }

        if (m_scene) {
            m_scene->update();
        }
    }

public:
    GraphicsLine(Line* l, QGraphicsScene* s) : m_model(l) {
        setScene(s);
        setZValue(0);
        updateVisual();
    }

    void setHovered(bool h) {
        m_hovered = h;
        updateVisual();
    }

    void setSelectedVisual(bool s) override {
        m_selected = s;
        updateVisual();
    }

    void attach() override {
        m_model->addObserver(this);
        sync();
    }

    std::vector<Point*> intersect(GraphicsLine* other) {
        std::vector<Point*> intersections;

        //if (boundingRect().intersects(other->boundingRect())) {
        return m_model->intersect(other->model(), other->lineType(), lineType());
        //}

        return intersections;
    }

    Line* model() override {
        return m_model;
    }

    void sync() override {
        setLine(m_model->x1(), m_model->y1(), m_model->x2(), m_model->y2());
    }
};

#endif // GRAPHICSLINE_H
