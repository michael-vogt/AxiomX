#include "createcirclecommand.h"

CreateCircleCommand::CreateCircleCommand(SceneController* c, GraphicsPoint* center, GraphicsPoint* pointOnCircle)
    : m_ctrl(c), m_center(center), m_pointOnCircle(pointOnCircle) {}

void CreateCircleCommand::execute() {
    m_circle = new Circle(m_center->model(), m_pointOnCircle->model());
    m_gcircle = new GraphicsCircle(m_circle, m_ctrl->scene());

    m_ctrl->scene()->addItem(m_gcircle);
    m_gcircle->attach();

    m_ctrl->graphics().push_back(m_gcircle);
}

void CreateCircleCommand::undo() {
    m_ctrl->scene()->removeItem(m_gcircle);
    auto graphics = m_ctrl->graphics();
    graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gcircle), graphics.end());
}

Circle* CreateCircleCommand::getResult() {
    return m_circle;
}

GraphicsCircle* CreateCircleCommand::getResultGraphicsObject() {
    return m_gcircle;
}