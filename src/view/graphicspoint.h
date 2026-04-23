#ifndef GRAPHICSPOINT_H
#define GRAPHICSPOINT_H

#include <QGraphicsEllipseItem>
#include "graphicsobject.h"
#include "../core/point.h"

class GraphicsPoint : public QGraphicsEllipseItem, public GraphicsObject {
private:
    Point* m_model;
    bool m_hovered = false;
    bool m_updating = false;

    QColor m_normalColor = Qt::blue;
    QColor m_hoverColor = Qt::green;
    QColor m_selectColor = Qt::red;

    void updateVisual();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

public:
    GraphicsPoint(Point* p, QGraphicsScene* s);

    void setHovered(bool h);

    void setSelectedVisual(bool s) override;

    void attach() override;

    Point* model() override;

    void sync() override;
};

#endif // GRAPHICSPOINT_H
