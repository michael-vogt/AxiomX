#include "graphicspoint.h"

void GraphicsPoint::updateVisual() {
    if (m_selected) {
        setBrush(m_selectColor);
    } else if (m_hovered) {
        setBrush(m_hoverColor);
    } else {
        setBrush(m_normalColor);
    }

    if (m_scene) {
        m_scene->update();
    }
}

QVariant GraphicsPoint::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && !m_updating) {
        QPointF newPos = value.toPointF();
        m_model->set(newPos.x(), newPos.y());
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

GraphicsPoint::GraphicsPoint(Point* p, QGraphicsScene* s) : QGraphicsEllipseItem(-5, -5, 10, 10), m_model(p) {
    setScene(s);
    setZValue(1);
    updateVisual();
}

void GraphicsPoint::setHovered(bool h) {
    m_hovered = h;
    updateVisual();
}

void GraphicsPoint::setSelectedVisual(bool s) {
    m_selected = s;
    updateVisual();
}

void GraphicsPoint::attach() {
    m_model->addObserver(this);
    sync();
}

Point* GraphicsPoint::model() {
    return m_model;
}

void GraphicsPoint::sync() {
    m_updating = true;
    setPos(m_model->x(), m_model->y());
    m_updating = false;
}