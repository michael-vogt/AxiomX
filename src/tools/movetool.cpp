#include "movetool.h"

MoveTool::MoveTool(SceneController* c) : Tool(nullptr), m_ctrl(c) {}

void MoveTool::resetTool() {}

void MoveTool::mousePress(const QPointF &pos) {
    m_selected = m_ctrl->findPointNear(pos);
}

void MoveTool::mouseMove(const QPointF &pos) {
    if (m_selected) {
        m_selected->set(pos.x(), pos.y());
        m_ctrl->scene()->update();
    }
}

void MoveTool::mouseRelease(const QPointF &pos) {
    m_selected = nullptr;
}