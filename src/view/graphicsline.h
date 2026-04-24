#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "graphicsobject.h"
#include "../core/line.h"

class GraphicsLine : public QGraphicsLineItem, public GraphicsObject {
private:
    Line* m_model;
    bool m_hovered = false;

    LineType m_lineType;
    QRectF m_boundingRect;

    QPen m_normalPen = QPen(Qt::black, 2);
    QPen m_hoverPen = QPen(Qt::green, 2);
    QPen m_selectPen = QPen(Qt::red, 2);

    void updateVisual();

public:
    GraphicsLine(Line* l, LineType lt, QGraphicsScene* s);

    QRectF boundingRect() const override;

    LineType lineType();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setHovered(bool h);

    void setLineType(LineType lineType);

    void setSelectedVisual(bool s) override;

    void attach() override;

    std::vector<Point*> intersect(GraphicsLine* other);

    Line* model() override;

    void sync() override;
};

#endif // GRAPHICSLINE_H
