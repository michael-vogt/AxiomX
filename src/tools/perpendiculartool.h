#ifndef PERPENDICULARTOOL_H
#define PERPENDICULARTOOL_H

#include "tool.h"
#include "../command/commandmanager.h"
#include "../control/scenecontroller.h"
#include "../view/graphicsline.h"

class PerpendicularTool : public Tool {
private:
    SceneController* m_ctrl;
    CommandManager* m_command;
    SnapManager* m_snap;

    GraphicsLine* m_line;

    QLineF perpendicularLine(GraphicsLine* line, GraphicsPoint* p);

public:
    PerpendicularTool(SceneController* s, CommandManager* c, SnapManager* sm);

    void mousePress(const QPointF& pos) override;

    void resetTool() override;
};

#endif // PERPENDICULARTOOL_H
