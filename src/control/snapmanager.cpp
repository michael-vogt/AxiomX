#include "snapmanager.h"
#include "../view/graphicspoint.h"

SnapManager::SnapManager(SceneController* c) : ctrl(c) {}

SnapResult SnapManager::snap(const QPointF& input) {
    // Priorität:
    // 1. Punkte
    // 2. Achsen
    // 3. Grid

    QPointF p = input;

    // 🔵 1. Punkte
    if (snapToPoints) {
        for (auto g : ctrl->graphics()) {
            if (auto gp = dynamic_cast<GraphicsPoint*>(g)) {
                if (QLineF(gp->pos(), input).length() < snapRadius) {
                    return { gp->pos(), true };
                }
            }
        }
    }

    // 🔴 2. Achsen
    if (snapToAxes) {
        if (std::abs(input.x()) < snapRadius)
            return { QPointF(0, input.y()), true };

        if (std::abs(input.y()) < snapRadius)
            return { QPointF(input.x(), 0), true };
    }

    // 🔲 3. Grid
    if (snapToGrid) {
        double gx = std::round(input.x() / gridSize) * gridSize;
        double gy = std::round(input.y() / gridSize) * gridSize;

        QPointF gridPoint(gx, gy);

        if (QLineF(gridPoint, input).length() < snapRadius)
            return { gridPoint, true };
    }

    return { input, false };
}
