#include "createpointcommand.h"

CreatePointCommand::CreatePointCommand(SceneController* c, double x, double y, bool isTemporaryPoint)
    : m_ctrl(c), m_x(x), m_y(y), m_isTemporaryPoint(isTemporaryPoint) {}

void CreatePointCommand::execute() {
    if (!m_point) {
        m_point = new Point(m_x, m_y);
        if (m_ctrl->pointExists(m_point) && !m_isTemporaryPoint) {
            qDebug() << "Punkt existiert bereits: " << QString::number(m_x) << ", " << QString::number(m_y);
            return;
        }
        m_gpoint = new GraphicsPoint(m_point, m_ctrl->scene());
    }

    m_ctrl->scene()->addItem(m_gpoint);
    m_gpoint->attach();

    m_ctrl->graphics().push_back(m_gpoint);
}

void CreatePointCommand::undo() {
    m_ctrl->scene()->removeItem(m_gpoint);
    auto graphics = m_ctrl->graphics();
    graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gpoint), graphics.end());
}

Point* CreatePointCommand::getResult() {
    return m_point;
}

GraphicsPoint* CreatePointCommand::getResultGraphicsObject() {
    return m_gpoint;
}