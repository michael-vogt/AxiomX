#ifndef INTERSECTIONTOOL_H
#define INTERSECTIONTOOL_H

#include "tool.h"
#include "../view/graphicsobject.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"

class IntersectionTool : public Tool {
private:
    GraphicsObject* m_object1 = nullptr;
    SceneController* m_ctrl = nullptr;
    CommandManager* m_command;
    std::vector<Point*> m_intersectionPoints;

    void findIntesections(GraphicsObject* obj1, GraphicsObject* obj2);

public:
    IntersectionTool(SceneController* c, CommandManager* cm);
    void resetTool() override;

    void mousePress(const QPointF& pos) override;

};

#endif // INTERSECTIONTOOL_H
