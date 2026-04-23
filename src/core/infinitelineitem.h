#ifndef INFINITELINEITEM_H
#define INFINITELINEITEM_H

#include <QGraphicsLineItem>
#include "../view/enums.h"

class InfiniteLineItem : public QGraphicsLineItem {
private:
    LineType m_lineType = LineType::LINE;

public:
    using QGraphicsLineItem::QGraphicsLineItem;

    InfiniteLineItem(LineType lineType);

    LineType lineType();

    void setLineType(LineType lineType);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // INFINITELINEITEM_H
