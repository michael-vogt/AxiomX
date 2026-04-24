#include "intersectiontool.h"
#include "../command/createpointcommand.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"

IntersectionTool::IntersectionTool(SceneController* c, CommandManager* cm) : Tool(nullptr), m_ctrl(c), m_command(cm) {}

void IntersectionTool::resetTool() {
    if (m_object1) {
        m_object1->setSelectedVisual(false);
        m_object1 = nullptr;
    }
}

void IntersectionTool::mousePress(const QPointF& pos) {
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

void IntersectionTool::findIntesections(GraphicsObject* obj1, GraphicsObject* obj2) {
    if (!obj1 || !obj2) return;

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
        if (gp) {
            gp->model()->addDependent(obj1->model());
            gp->model()->addDependent(obj2->model());
        }
    }
}