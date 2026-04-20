#ifndef INTERSECTIONTOOL_H
#define INTERSECTIONTOOL_H

#include "tool.h"
#include "../view/graphicsobject.h"
#include "../control/scenecontroller.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"

class IntersectionTool : public Tool {
private:
    GraphicsObject* m_object1 = nullptr;
    SceneController* m_ctrl = nullptr;
    CommandManager* m_command;
    std::vector<Point*> m_intersectionPoints;

public:
    IntersectionTool(SceneController* c, CommandManager* cm) : m_ctrl(c), m_command(cm) {}
    void resetTool() override {
        if (m_object1) {
            m_object1->setSelectedVisual(false);
            m_object1 = nullptr;
        }
    }

    void mousePress(const QPointF& pos) override {
        GraphicsObject* g = m_ctrl->findObjectAt(pos);
        if (!g) return;

        auto gp = dynamic_cast<GraphicsPoint*>(g);
        if (gp) return;

        if (!m_object1) {
            m_object1 = g;
            m_object1->setSelectedVisual(true);
        } else {
            findIntesections(m_object1, g);
            resetTool();
        }
    }

private:
    void findIntesections(GraphicsObject* obj1, GraphicsObject* obj2) {
        auto gl1 = dynamic_cast<GraphicsLine*>(obj1);
        auto gc1 = dynamic_cast<GraphicsCircle*>(obj1);

        auto gl2 = dynamic_cast<GraphicsLine*>(obj2);
        auto gc2 = dynamic_cast<GraphicsCircle*>(obj2);

        if (gc1 && gc2) { // Circle - Circle intersection
            m_intersectionPoints = gc1->intersect(gc2);
        } else if (gc1 && gl2) {
            m_intersectionPoints = gc1->intersect(gl2);
        } else if (gl1 && gc2) {
            m_intersectionPoints = gc2->intersect(gl1);
        } else if (gl1 && gl2) {
            m_intersectionPoints = gl1->intersect(gl2);
        }

        for (Point* p : m_intersectionPoints) {
            auto cmd = new CreatePointCommand(m_ctrl, p->x(), p->y());
            m_command->execute(cmd);
            GraphicsPoint* gp = cmd->getResultGraphicsObject();
            gp->model()->addDependent(obj1->model());
            gp->model()->addDependent(obj2->model());
        }
    }
};

#endif // INTERSECTIONTOOL_H
