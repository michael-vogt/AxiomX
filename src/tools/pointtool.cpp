#include "pointtool.h"
#include "../command/createpointcommand.h"

PointTool::PointTool(SceneController* c, CommandManager* cm, SnapManager* sm) : Tool(sm),  m_ctrl(c), m_commandManager(cm) {}

void PointTool::resetTool() {}

void PointTool::mousePress(const QPointF &pos) {
    m_commandManager->execute(new CreatePointCommand(m_ctrl, pos.x(), pos.y()));
}