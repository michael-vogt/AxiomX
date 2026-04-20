#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../core/utility.h"

class PointTool : public Tool {
private:
    SceneController* m_ctrl;
    CommandManager* m_commandManager;

public:
    PointTool(SceneController* c, CommandManager* cm) : m_ctrl(c), m_commandManager(cm) {}

    void resetTool() override {}

    void mousePress(const QPointF &pos) override {
        m_commandManager->execute(new CreatePointCommand(m_ctrl, pos.x(), pos.y()));
    }
};

#endif // POINTTOOL_H
