#include "createlinecommand.h"

CreateLineCommand::CreateLineCommand(SceneController* c, GraphicsPoint* a, GraphicsPoint* b, LineType lineType)
    : m_ctrl(c), m_a(a), m_b(b), m_lineType(lineType) {}

void CreateLineCommand::execute() {
    m_line = new Line(m_a->model(), m_b->model());
    m_gline = new GraphicsLine(m_line, m_lineType, m_ctrl->scene());
    m_gline->setLineType(m_lineType);

    m_ctrl->scene()->addItem(m_gline);
    m_gline->attach();

    m_ctrl->graphics().push_back(m_gline);
}

void CreateLineCommand::undo() {
    m_ctrl->scene()->removeItem(m_gline);
    auto graphics = m_ctrl->graphics();
    graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gline), graphics.end());
}

Line* CreateLineCommand::getResult() {
    return m_line;
}

GraphicsLine* CreateLineCommand::getResultGraphicsObject() {
    return m_gline;
}