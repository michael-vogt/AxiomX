#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"
#include "../control/interactionmanager.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"

class LineTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;
    CommandManager* m_command;

    GraphicsPoint* m_first = nullptr;
    InfiniteLineItem* m_preview = nullptr;

    LineType m_lineType = LineType::LINE;

public:
    LineTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm);

    LineType lineType();

    void toggleLineType();

    void resetTool() override;

    void mousePress(const QPointF &pos) override;

    void mouseMove(const QPointF& pos) override;

    void mouseRelease(const QPointF&) override;

};

#endif // LINETOOL_H
