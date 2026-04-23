#ifndef GRID_H
#define GRID_H

#include <QPainter>

class Grid {
private:
    std::vector<QLineF> m_gridLines;
    std::vector<QPointF> m_gridPoints;
    QPointF m_origin;
    QPointF m_panning = QPointF(0, 0);
    QRectF m_sceneRect;
    double m_scaleFactor = 1.0;
    double m_unitsPerPixel = 0.01;

public:
    Grid(QPointF origin, QRectF sceneRect);

    void update(QRectF sceneRect);

    void paint(QPainter* painter);

    QPointF snapToGrid(QPointF pos, double delta = 6.0);

    std::vector<QLineF>& gridLines();

private:
    void init();
};

#endif // GRID_H
