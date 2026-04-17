#ifndef INFINITELINEITEM_H
#define INFINITELINEITEM_H

#include <QGraphicsLineItem>
#include <QPainter>

enum LineType {
    SEGMENT = 0,
    RAY = 1,
    LINE = 2
};

class InfiniteLineItem : public QGraphicsLineItem {
private:
    LineType m_lineType = LineType::LINE;

public:
    using QGraphicsLineItem::QGraphicsLineItem;

    InfiniteLineItem(LineType lineType) : m_lineType(lineType) {}

    void setLineType(LineType lineType) {
        m_lineType = lineType;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        QRectF rect = painter->viewport();

        QLineF base = line();
        QLineF dir = base.unitVector();
        QPointF d = dir.p2() - dir.p1();

        QPointF start = base.pointAt(0), end = base.pointAt(1);
        if (m_lineType == LineType::LINE) {
            start -= d * 1e6;
            end += d * 1e6;
        } else if (m_lineType == LineType::RAY) {
            end += d * 1e6;
        }

        QLineF longLine(start, end);

        painter->setPen(this->pen());
        painter->drawLine(longLine);

    }
};

#endif // INFINITELINEITEM_H
