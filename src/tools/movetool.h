#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"

class MoveTool : public Tool {
private:
    SceneController* m_ctrl;
    Point* m_selected = nullptr;

public:
    MoveTool(SceneController* c);

    void resetTool() override;

    void mousePress(const QPointF &pos) override;

    void mouseMove(const QPointF &pos) override;

    void mouseRelease(const QPointF &pos) override;
};

#endif // MOVETOOL_H
