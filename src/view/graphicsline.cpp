#include "graphicsline.h"

void GraphicsLine::updateVisual() {
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

GraphicsLine::GraphicsLine(Line* l, QGraphicsScene* s) : m_model(l) {
    setScene(s);
    setZValue(0);
    updateVisual();
}

void GraphicsLine::setHovered(bool h) {
    m_hovered = h;
    updateVisual();
}

void GraphicsLine::setSelectedVisual(bool s) {
    m_selected = s;
    updateVisual();
}

void GraphicsLine::attach() {
    m_model->addObserver(this);
    sync();
}

std::vector<Point*> GraphicsLine::intersect(GraphicsLine* other) {
    std::vector<Point*> intersections;

    //if (boundingRect().intersects(other->boundingRect())) {
    return m_model->intersect(other->model(), other->lineType(), lineType());
    //}

    return intersections;
}

Line* GraphicsLine::model() {
    return m_model;
}

void GraphicsLine::sync() {
    setLine(m_model->x1(), m_model->y1(), m_model->x2(), m_model->y2());
}