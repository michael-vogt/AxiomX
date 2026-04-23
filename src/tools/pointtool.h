#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"
#include "../view/grid.h"

class PointTool : public Tool {
private:
    SceneController* m_ctrl;
    CommandManager* m_commandManager;
    Grid* m_grid = nullptr;

public:
    PointTool(SceneController* c, CommandManager* cm, Grid* g);

    void resetTool() override;

    void mousePress(const QPointF &pos) override;

};

#endif // POINTTOOL_H
