#ifndef GRID_H
#define GRID_H

#include <QDebug>
#include <QLineF>
#include <QRectF>
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
    Grid(QPointF origin, QRectF sceneRect) : m_origin(origin), m_sceneRect(sceneRect) {
        init();
    }

    void update(QRectF sceneRect) {
        m_sceneRect = sceneRect;
        m_origin = sceneRect.center();
        m_gridLines.clear();
        m_gridPoints.clear();
        init();

    }

    void paint(QPainter* painter) {
        QLineF axisX(0, m_origin.y(), m_sceneRect.width(), m_origin.y());
        QLineF axisY(m_origin.x(), 0, m_origin.x(), m_sceneRect.height());

        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(axisX);
        painter->drawLine(axisY);

        painter->setPen(QPen(Qt::gray, 2));
        for (QPointF& point : m_gridPoints) {
            painter->drawPoint(point.x() + m_origin.x(), point.y() + m_origin.y());
        }
    }

    QPointF snapToGrid(QPointF pos, double delta = 6.0) {
        QList<QPointF> candidates;
        QPointF posT = pos - m_origin;
        QRectF boundingBox = QRectF(posT.x() - delta / 2, posT.y() - delta / 2, delta, delta);
        //boundingBox.translate(-m_origin);
        for (QPointF& p : m_gridPoints) {
            if (boundingBox.contains(p)) {
                candidates.append(p);
            }
        }

        if (candidates.isEmpty()) return pos;

        QPointF snappedPoint = pos;
        double minDistance = -1;
        for (QPointF p : candidates) {
            double distance = QLineF(p, posT).length();
            if (minDistance == -1 || distance < minDistance) {
                minDistance = distance;
                snappedPoint = p + m_origin;
            }
        }

        if (minDistance < delta) {
            return snappedPoint;
        }

        return pos;
    }

    std::vector<QLineF>& gridLines() {
        return m_gridLines;
    }

private:
    void init() {
        double w = m_sceneRect.width();
        double h = m_sceneRect.height();
        int n = w * m_unitsPerPixel;
        int m = h * m_unitsPerPixel;
        double dx = w / (2 * n + 1);
        double dy = h / (2 * m + 1);

        QLineF lineH = QLineF(0, 0, w, 0).translated(-m_origin.x(), 0);
        QLineF lineV = QLineF(0, 0, 0, h).translated(0, -m_origin.y());

        for (int i = -n; i <= n; i++) {
            for (int j = -m; j <= m; j++) {
                //if (i == 0 || j == 0) continue;
                m_gridPoints.push_back(QPointF(i * dx, j * dy));
            }
        }

        for (int i = -n; i <= n; i++) {
            if (i == 0) continue;
            m_gridLines.push_back(lineV.translated(i * dx, 0));
        }

        for (int i = -m; i <= m; i++) {
            if (i == 0) continue;
            m_gridLines.push_back(lineH.translated(0, i * dy));
        }
    }
};

#endif // GRID_H
