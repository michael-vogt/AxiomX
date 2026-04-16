#ifndef INFINITELINEITEM_H
#define INFINITELINEITEM_H

#include <QGraphicsLineItem>
#include <QPainter>

class InfiniteLineItem : public QGraphicsLineItem {
public:
    using QGraphicsLineItem::QGraphicsLineItem;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        QRectF rect = painter->viewport();

        QLineF base = line();
        QLineF dir = base.unitVector();
        QPointF d = dir.p2() - dir.p1();

        QLineF longLine(
            base.pointAt(0) - d * 1e6,
            base.pointAt(0) + d * 1e6
            );

        painter->setPen(this->pen());
        painter->drawLine(longLine);

    }
};

#endif // INFINITELINEITEM_H
