#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "tool.h"
#include "../control/interactionmanager.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../command/createcirclecommand.h"

class CircleTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;
    CommandManager* m_command;

    GraphicsPoint* m_first = nullptr;
    QGraphicsEllipseItem* m_preview = nullptr;

public:
    CircleTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm);

    void resetTool() override;

    void mousePress(const QPointF& pos) override;

    void mouseMove(const QPointF& pos) override;

};

#endif // CIRCLETOOL_H
