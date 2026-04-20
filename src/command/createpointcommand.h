#ifndef CREATEPOINTCOMMAND_H
#define CREATEPOINTCOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"

class CreatePointCommand : public ResultCommand<Point*, GraphicsPoint*> {
public:
    SceneController* m_ctrl;
    double m_x, m_y;
    bool m_isTemporaryPoint;

    Point* m_point = nullptr;
    GraphicsPoint* m_gpoint = nullptr;

    CreatePointCommand(SceneController* c, double x, double y, bool isTemporaryPoint = false)
        : m_ctrl(c), m_x(x), m_y(y), m_isTemporaryPoint(isTemporaryPoint) {}

    void execute() override {
        if (!m_point) {
            m_point = new Point(m_x, m_y);
            if (m_ctrl->pointExists(m_point) && !m_isTemporaryPoint) {
                qDebug() << "Punkt existiert bereits: " << QString::number(m_x) << ", " << QString::number(m_y);
            }
            m_gpoint = new GraphicsPoint(m_point, m_ctrl->scene());
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

    GraphicsPoint* getResultGraphicsObject() override {
        return m_gpoint;
    }
};

#endif // CREATEPOINTCOMMAND_H
