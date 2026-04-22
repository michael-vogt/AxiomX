#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../core/utility.h"
#include "../view/grid.h"

class PointTool : public Tool {
private:
    SceneController* m_ctrl = nullptr;
    CommandManager* m_commandManager = nullptr;
    Grid* m_grid = nullptr;

public:
    PointTool(SceneController* c, CommandManager* cm, Grid* g) : m_ctrl(c), m_commandManager(cm), m_grid(g) {}

    void resetTool() override {}

    void mousePress(const QPointF &pos) override {
        QPointF snappedPoint = m_grid->snapToGrid(pos);
        m_commandManager->execute(new CreatePointCommand(m_ctrl, snappedPoint.x(), snappedPoint.y()));
    }
};

#endif // POINTTOOL_H
