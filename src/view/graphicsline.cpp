#include "graphicsline.h"

void GraphicsLine::updateVisual() {
    if (m_selected) {
        setPen(m_selectPen);
    } else if (m_hovered) {
        setPen(m_hoverPen);
    } else {
        setPen(m_normalPen);
    }

    if (m_scene) {
        m_scene->update();
    }
}

GraphicsLine::GraphicsLine(Line* l, LineType lt, QGraphicsScene* s) : m_model(l), m_lineType(lt) {
    setScene(s);
    setZValue(0);
    updateVisual();
}

QRectF GraphicsLine::boundingRect() const {
    QPointF p1(m_model->x1(), m_model->y1());
    QPointF p2(m_model->x2(), m_model->y2());

    QPointF dir = (p2 - p1);
    dir.setX(dir.x() * 1e6);
    dir.setY(dir.y() * 1e6);

    QPointF start = p1;
    if (m_lineType == LINE) {
        start -= dir;
    }

    QPointF end = p2;
    if (m_lineType != SEGMENT) {
        end += dir;
    }

    QPointF topLeft(std::min(start.x(), end.x()), std::min(start.y(), end.y()));
    QSizeF size(std::abs(end.x() - start.x()), std::abs(end.y() - start.y()));

    return QRectF(topLeft, size);

}

LineType GraphicsLine::lineType() {
    return m_lineType;
}

void GraphicsLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
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

void GraphicsLine::setHovered(bool h) {
    m_hovered = h;
    updateVisual();
}

void GraphicsLine::setLineType(LineType lineType) {
    m_lineType = lineType;
}

void GraphicsLine::setSelectedVisual(bool s) {
    m_selected = s;
    updateVisual();
}

void GraphicsLine::attach() {
    m_model->addObserver(this);
    sync();
}

std::vector<Point*> GraphicsLine::intersect(GraphicsLine* other) {
    std::vector<Point*> intersections;

    //if (boundingRect().intersects(other->boundingRect())) {
    return m_model->intersect(other->model(), other->lineType(), lineType());
    //}

    return intersections;
}

Line* GraphicsLine::model() {
    return m_model;
}

void GraphicsLine::sync() {
    setLine(m_model->x1(), m_model->y1(), m_model->x2(), m_model->y2());
}