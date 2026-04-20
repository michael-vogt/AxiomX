#ifndef GRAPHICSCIRCLE_H
#define GRAPHICSCIRCLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPen>
#include "graphicsobject.h"
#include "graphicsline.h"
#include "../core/circle.h"

class GraphicsCircle : public QGraphicsEllipseItem, public GraphicsObject {
private:
    Circle* m_model;
    bool m_hovered = false;
    bool m_selected = false;
    QGraphicsScene* m_scene;

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
    GraphicsCircle(Circle* c, QGraphicsScene* s) : m_model(c), m_scene(s) {
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

    std::vector<Point*> intersect(GraphicsCircle* other) {
        std::vector<Point*> intersections;

        if (boundingRect().intersects(other->boundingRect())) {
            return m_model->intersect(other->model());
        }

        return intersections;
    }

    std::vector<Point*> intersect(GraphicsLine* other) {
        std::vector<Point*> intersections;

        if (boundingRect().intersects(other->boundingRect())) {
            return m_model->intersect(other->model(), other->lineType());
        }

        return intersections;
    }

    Circle* model() override {
        return m_model;
    }

    void sync() override {
        double radius = m_model->radius();
        //QPointF center(m_model->center()->x() - radius, m_model->center()->y() - radius);
        QPointF center(m_model->x1() - radius, m_model->y1() - radius);
        setRect(center.x(), center.y(), 2 * radius, 2 * radius);
        //setLine(m_model->x1(), m_model->y1(), m_model->x2(), m_model->y2());
    }
};

#endif // GRAPHICSCIRCLE_H
