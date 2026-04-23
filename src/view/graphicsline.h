#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include "graphicsobject.h"
#include "../core/infinitelineitem.h"
#include "../core/line.h"

class GraphicsLine : public InfiniteLineItem, public GraphicsObject {
private:
    Line* m_model;
    bool m_hovered = false;

    QPen m_normalPen = QPen(Qt::black, 2);
    QPen m_hoverPen = QPen(Qt::green, 2);
    QPen m_selectPen = QPen(Qt::red, 2);

    void updateVisual();

public:
    GraphicsLine(Line* l, QGraphicsScene* s);

    void setHovered(bool h);

    void setSelectedVisual(bool s) override;

    void attach() override;

    std::vector<Point*> intersect(GraphicsLine* other);

    Line* model() override;

    void sync() override;
};

#endif // GRAPHICSLINE_H
