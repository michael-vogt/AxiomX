#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "../view/view.h"
#include "scenecontroller.h"

class InteractionManager {
public:
    SceneController* m_ctrl;

    GraphicsPoint* m_hoveredPoint = nullptr;
    GraphicsPoint* m_snappedPoint = nullptr;

    InteractionManager(SceneController* c) : m_ctrl(c) {}

    void updateHover(const QPointF& pos) {
        // Reset vorheriges Highlight
        if (m_hoveredPoint) {
            m_hoveredPoint->setHighlighted(false);
            m_hoveredPoint = nullptr;
        }

        // Suche neuen Punkt
        for (auto g : m_ctrl->graphics()) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            if (QLineF(gp->pos(), pos).length() < 10.0) {
                m_hoveredPoint = gp;
                gp->setHighlighted(true);
                break;
            }
        }
    }

    Point* getSnappedPoint(const QPointF& pos) {
        m_snappedPoint = nullptr;

        for (auto g : m_ctrl->graphics()) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            if (QLineF(gp->pos(), pos).length() < 10.0) {
                m_snappedPoint = gp;
                return gp->model();
            }
        }
        return nullptr;
    }
};

#endif // INTERACTIONMANAGER_H
