#include "pointtool.h"
#include "../command/createpointcommand.h"

PointTool::PointTool(SceneController* c, CommandManager* cm, Grid* g) : m_ctrl(c), m_commandManager(cm), m_grid(g) {}

void PointTool::resetTool() {}

void PointTool::mousePress(const QPointF &pos) {
    QPointF snappedPoint = m_grid->snapToGrid(pos);
    m_commandManager->execute(new CreatePointCommand(m_ctrl, snappedPoint.x(), snappedPoint.y()));
}