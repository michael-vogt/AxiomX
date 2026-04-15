#ifndef GRAPHICSPOINT_H
#define GRAPHICSPOINT_H

#include <QEvent>
#include <QGraphicsEllipseItem>
#include "../core/core.h"
#include "observer.h"
#include "graphicsobject.h"

class GraphicsPoint : public QGraphicsEllipseItem, public GraphicsObject {
private:
    Point* m_model;
    bool m_highlighted = false;
    bool m_updating = false;

    QColor m_normalColor = Qt::blue;
    QColor m_hoverColor = QColor(255, 140, 0);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && !m_updating) {
            QPointF newPos = value.toPointF();
            m_model->set(newPos.x(), newPos.y());
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

public:
    GraphicsPoint(Point* p) : QGraphicsEllipseItem(-5, -5, 10, 10), m_model(p) {
        setBrush(m_normalColor);
        setZValue(1);
    }

    void setHighlighted(bool h) {
        m_highlighted = h;

        if (h) {
            setBrush(m_hoverColor);
        } else {
            setBrush(m_normalColor);
        }
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
};

#endif // GRAPHICSPOINT_H
