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

    QPen m_normalPen = QPen(Qt::black, 2);
    QPen m_hoverPen = QPen(Qt::green, 2);
    QPen m_selectPen = QPen(Qt::red, 2);

    void updateVisual();

public:
    GraphicsCircle(Circle* c, QGraphicsScene* s);

    void setHovered(bool h);

    void setSelectedVisual(bool s) override;

    void attach() override;

    std::vector<Point*> intersect(GraphicsCircle* other);

    std::vector<Point*> intersect(GraphicsLine* other);

    Circle* model() override;

    void sync() override;
};

#endif // GRAPHICSCIRCLE_H
