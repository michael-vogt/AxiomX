#include "graphicscircle.h"

GraphicsCircle::GraphicsCircle(Circle* c, QGraphicsScene* s) : m_model(c) {
    setScene(s);
    setZValue(0);
    updateVisual();
}

void GraphicsCircle::updateVisual() {
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

void GraphicsCircle::setHovered(bool h) {
    m_hovered = h;
    updateVisual();
}

void GraphicsCircle::setSelectedVisual(bool s) {
    m_selected = s;
    updateVisual();
}

void GraphicsCircle::attach() {
    m_model->addObserver(this);
    sync();
}

std::vector<Point*> GraphicsCircle::intersect(GraphicsCircle* other) {
    std::vector<Point*> intersections;

    if (boundingRect().intersects(other->boundingRect())) {
        return m_model->intersect(other->model());
    }

    return intersections;
}

std::vector<Point*> GraphicsCircle::intersect(GraphicsLine* other) {
    std::vector<Point*> intersections;

    if (boundingRect().intersects(other->boundingRect())) {
        return m_model->intersect(other->model(), other->lineType());
    }

    return intersections;
}

Circle* GraphicsCircle::model() {
    return m_model;
}

void GraphicsCircle::sync() {
    double radius = m_model->radius();
    QPointF center(m_model->x1() - radius, m_model->y1() - radius);
    setRect(center.x(), center.y(), 2 * radius, 2 * radius);
}