#ifndef CREATEPOINTCOMMAND_H
#define CREATEPOINTCOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"

class CreatePointCommand : public ResultCommand<Point*> {
public:
    SceneController* m_ctrl;
    double m_x, m_y;

    Point* m_point = nullptr;
    GraphicsPoint* m_gpoint = nullptr;

    CreatePointCommand(SceneController* c, double x, double y)
        : m_ctrl(c), m_x(x), m_y(y) {}

    void execute() override {
        if (!m_point) {
            m_point = new Point(m_x, m_y);
            m_gpoint = new GraphicsPoint(m_point);
        }

        m_ctrl->scene()->addItem(m_gpoint);
        m_gpoint->attach();

        m_ctrl->graphics().push_back(m_gpoint);
    }

    void undo() override {
        m_ctrl->scene()->removeItem(m_gpoint);
        auto graphics = m_ctrl->graphics();
        graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gpoint), graphics.end());
    }

    Point* getResult() override {
        return m_point;
    }
};

#endif // CREATEPOINTCOMMAND_H
