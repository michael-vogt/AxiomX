#ifndef CREATECIRCLECOMMAND_H
#define CREATECIRCLECOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"
#include "../view/graphicscircle.h"

class CreateCircleCommand : public ResultCommand<Circle*, GraphicsCircle*> {
public:
    SceneController* m_ctrl;
    GraphicsPoint* m_center;
    GraphicsPoint* m_pointOnCircle;
    //double m_radius;

    Circle* m_circle = nullptr;
    GraphicsCircle* m_gcircle = nullptr;

    CreateCircleCommand(SceneController* c, GraphicsPoint* center, GraphicsPoint* pointOnCircle)
        : m_ctrl(c), m_center(center), m_pointOnCircle(pointOnCircle) {}

    void execute() override {
        m_circle = new Circle(m_center->model(), m_pointOnCircle->model());
        m_gcircle = new GraphicsCircle(m_circle, m_ctrl->scene());

        m_ctrl->scene()->addItem(m_gcircle);
        m_gcircle->attach();

        m_ctrl->graphics().push_back(m_gcircle);
    }

    void undo() override {
        m_ctrl->scene()->removeItem(m_gcircle);
        auto graphics = m_ctrl->graphics();
        graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gcircle), graphics.end());
    }

    Circle* getResult() override {
        return m_circle;
    }

    GraphicsCircle* getResultGraphicsObject() override {
        return m_gcircle;
    }
};

#endif // CREATECIRCLECOMMAND_H
