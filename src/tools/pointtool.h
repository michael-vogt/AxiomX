#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"

class PointTool : public Tool {
private:
    SceneController* m_ctrl;
    CommandManager* m_commandManager;

public:
    PointTool(SceneController* c, CommandManager* cm, SnapManager* sm);

    void resetTool() override;

    void mousePress(const QPointF &pos) override;

};

#endif // POINTTOOL_H
