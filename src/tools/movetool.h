#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"

class MoveTool : public Tool {
private:
    SceneController* m_ctrl;
    Point* m_selected = nullptr;

public:
    MoveTool(SceneController* c) : m_ctrl(c) {}

    void resetTool() override {}

    void mousePress(const QPointF &pos) override {
        m_selected = m_ctrl->findPointNear(pos);
    }

    void mouseMove(const QPointF &pos) override {
        if (m_selected) {
            m_selected->set(pos.x(), pos.y());
        }
    }

    void mouseRelease(const QPointF &pos) override {
        m_selected = nullptr;
    }
};

#endif // MOVETOOL_H
