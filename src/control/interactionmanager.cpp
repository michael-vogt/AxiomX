#include "interactionmanager.h"

InteractionManager::InteractionManager(SceneController* c) : m_ctrl(c) {}

void InteractionManager::clearHover() {
    if (m_hoveredPoint) {
        m_hoveredPoint->setHovered(false);
        m_hoveredPoint = nullptr;
    }

    if (m_hoveredLine) {
        m_hoveredLine->setHovered(false);
        m_hoveredLine = nullptr;
    }

    if (m_hoveredCircle) {
        m_hoveredCircle->setHovered(false);
        m_hoveredCircle = nullptr;
    }
}

void InteractionManager::updateHover(const QPointF& pos) {
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

        if (gl->model()->distanceToPoint(pos, gl->lineType()) < 6.0) {
            m_hoveredLine = gl;
            gl->setHovered(true);
            return;
        }
    }

    // Kreise prüfen
    for (auto g : m_ctrl->graphics()) {
        auto gc = dynamic_cast<GraphicsCircle*>(g);
        if (!gc) continue;

        if (gc->model()->pointOnCircle(pos, 6.0)) {
            m_hoveredCircle = gc;
            gc->setHovered(true);
            return;
        }
    }
}