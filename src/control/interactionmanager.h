#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

/*#include "../view/view.h"
#include "scenecontroller.h"*/
#include "scenecontroller.h"

class InteractionManager {
public:
    SceneController* m_ctrl;

    GraphicsPoint* m_hoveredPoint = nullptr;
    GraphicsPoint* m_snappedPoint = nullptr;
    GraphicsLine* m_hoveredLine = nullptr;

    InteractionManager(SceneController* c) : m_ctrl(c) {}

    void clearHover() {
        if (m_hoveredPoint) {
            m_hoveredPoint->setHovered(false);
            m_hoveredPoint = nullptr;
        }

        if (m_hoveredLine) {
            m_hoveredLine->setHovered(false);
            m_hoveredLine = nullptr;
        }
    }

    void updateHover(const QPointF& pos) {
        clearHover();

        // Punkte prüfen
        for (auto g : m_ctrl->graphics()) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            if (QLineF(gp->pos(), pos).length() < 10.0) {
                m_hoveredPoint = gp;
                gp->setHovered(true);
                return;
            }
        }

        // Linien prüfen
        for (auto g : m_ctrl->graphics()) {
            auto gl = dynamic_cast<GraphicsLine*>(g);
            if (!gl) continue;

            if (gl->model()->distanceToPoint(pos) < 6.0) {
                m_hoveredLine = gl;
                gl->setHovered(true);
                return;
            }
        }
    }

    GraphicsPoint* getSnappedPoint(const QPointF& pos) {
        m_snappedPoint = nullptr;

        for (auto g : m_ctrl->graphics()) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            if (QLineF(gp->pos(), pos).length() < 10.0) {
                m_snappedPoint = gp;
                return gp;
            }
        }
        return nullptr;
    }
};

#endif // INTERACTIONMANAGER_H
