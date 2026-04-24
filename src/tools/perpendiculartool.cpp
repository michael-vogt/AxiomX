#include "perpendiculartool.h"
#include "../view/graphicspoint.h"
#include "../command/createlinecommand.h"

PerpendicularTool::PerpendicularTool(SceneController* s, CommandManager* c, SnapManager* sm) : Tool(sm), m_ctrl(s), m_command(c) {}

void PerpendicularTool::mousePress(const QPointF& pos) {
    GraphicsObject* g = m_ctrl->findObjectAt(pos);
    if (!g) return;

    if (!m_line) { // zunächst muss eine Linie ausgewählt werden...
        GraphicsLine* gl = dynamic_cast<GraphicsLine*>(g);
        if (!gl) return;

        m_line = gl;
        m_line->setSelectedVisual(true);
    } else { // ... und dann ein Punkt
        GraphicsPoint* gp1 = dynamic_cast<GraphicsPoint*>(g);
        if (!gp1) return;

        QLineF pLine = perpendicularLine(m_line, gp1);
        GraphicsPoint* gp2 = new GraphicsPoint(new Point(pLine.p2().x(), pLine.p2().y()), m_ctrl->scene());

        auto cmd = new CreateLineCommand(m_ctrl, gp1, gp2, LineType::LINE);
        m_command->execute(cmd);
        resetTool();
    }
}

QLineF PerpendicularTool::perpendicularLine(GraphicsLine* line, GraphicsPoint* p) {
    QPointF p1(p->model()->x(), p->model()->y());
    Line* lineModel = line->model();
    double dx = lineModel->x2() - lineModel->x1();
    double dy = lineModel->y2() - lineModel->y1();

    QPointF p2;
    if (std::abs(dy) < 1e-10) { // horizontale Linie
        p2 = QPointF(p1.x(), p1.y() + dx);
    } else {
        p2 = p1 + QPointF(-dy, dx);
    }

    return QLineF(p1, p2);
}

void PerpendicularTool::resetTool() {
    if (m_line) {
        m_line->setSelectedVisual(false);
        m_line = nullptr;
    }
}
