#ifndef GRAPHICSPOINT_H
#define GRAPHICSPOINT_H

#include <QEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include "../core/core.h"
#include "observer.h"
#include "graphicsobject.h"

class GraphicsPoint : public QGraphicsEllipseItem, public GraphicsObject {
private:
    Point* m_model;
    bool m_hovered = false;
    bool m_updating = false;

    QColor m_normalColor = Qt::blue;
    QColor m_hoverColor = Qt::green;
    QColor m_selectColor = Qt::red;

    void updateVisual() {
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

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && !m_updating) {
            QPointF newPos = value.toPointF();
            m_model->set(newPos.x(), newPos.y());
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

public:
    GraphicsPoint(Point* p, QGraphicsScene* s) : QGraphicsEllipseItem(-5, -5, 10, 10), m_model(p) {
        setScene(s);
        setZValue(1);
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

    Point* model() override {
        return m_model;
    }

    void sync() override {
        m_updating = true;
        setPos(m_model->x(), m_model->y());
        m_updating = false;
    }

    bool equals(GraphicsPoint* other) {
        if (!other || !m_model) return false;
        return (m_model->x() == other->model()->x() && m_model->y() == other->model()->y());
    }
};

#endif // GRAPHICSPOINT_H
