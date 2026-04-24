#include "snapmanager.h"
#include "../view/graphicspoint.h"

SnapManager::SnapManager(SceneController* c) : m_ctrl(c) {}

SnapResult SnapManager::snap(const QPointF& input) {
    // Priorität:
    // 1. Punkte
    // 2. Grid
    // 3. Achsen

    QPointF p = input;

    // 🔵 1. Punkte
    if (m_snapToPoints) {
        for (auto g : m_ctrl->graphics()) {
            if (auto gp = dynamic_cast<GraphicsPoint*>(g)) {
                if (QLineF(gp->pos(), input).length() < m_snapRadius) {
                    return { gp, gp->pos(), true };
                }
            }
        }
    }

    // 🔲 2. Grid
    if (m_snapToGrid) {
        double gx = std::round(input.x() / m_gridSize) * m_gridSize;
        double gy = std::round(input.y() / m_gridSize) * m_gridSize;

        QPointF gridPoint(gx, gy);

        if (QLineF(gridPoint, input).length() < m_snapRadius)
            return { nullptr, gridPoint, true };
    }

    // 🔴 3. Achsen
    if (m_snapToAxes) {
        if (std::abs(input.x()) < m_snapRadius)
            return { nullptr, QPointF(0, input.y()), true };

        if (std::abs(input.y()) < m_snapRadius)
            return { nullptr, QPointF(input.x(), 0), true };
    }

    return { nullptr, input, false };
}
