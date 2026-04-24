#include "linetool.h"
#include "../command/createlinecommand.h"
#include "../command/createpointcommand.h"

LineTool::LineTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm, SnapManager* sm) : Tool(sm), m_ctrl(c), m_interaction(im), m_scene(s), m_command(cm) {}

LineType LineTool::lineType() {
    return m_lineType;
}

void LineTool::toggleLineType() {
    if (m_lineType == LineType::SEGMENT) {
        m_lineType = LineType::RAY;
    } else if (m_lineType == LineType::RAY) {
        m_lineType = LineType::LINE;
    } else {
        m_lineType = LineType::SEGMENT;
    }
}

void LineTool::resetTool() {
    bool update = (m_preview || m_first);
    if (m_preview) {
        m_scene->removeItem(m_preview);
        delete m_preview;
        m_preview = nullptr;
    }

    if (m_first) {
        m_scene->removeItem(m_first);
        m_first = nullptr;
    }

    m_currentlyWorking = false;

    if (update) {
        m_scene->update();
    }
}

void LineTool::mousePress(const QPointF &pos) {
    SnapResult res = m_snap->snap(pos);
    GraphicsPoint* p = res.gp;
    if (!p) {
        auto cmd = new CreatePointCommand(m_ctrl, res.pos.x(), res.pos.y());
        m_command->execute(cmd);
        p = cmd->getResultGraphicsObject();
    }

    if (!m_first) {
        m_first = p;

        QPen pen(Qt::DashLine);
        pen.setColor(Qt::gray);
        pen.setWidth(2);

        Point* a = new Point(pos.x(), pos.y());
        m_preview = new GraphicsLine(new Line(a, a), m_lineType, m_scene);
        m_preview->setPen(pen);
        m_scene->addItem(m_preview);

        m_currentlyWorking = true;
    } else {
        auto cmd = new CreateLineCommand(m_ctrl, m_first, p, m_lineType);
        m_command->execute(cmd);

        if (m_preview) {
            m_scene->removeItem(m_preview);
            delete m_preview;
            m_preview = nullptr;
        }

        m_first = nullptr;
        m_scene->update();
        m_currentlyWorking = false;
    }
}

void LineTool::mouseMove(const QPointF& pos) {
    if (!m_first || !m_preview) return;

    QPointF target = pos;
    SnapResult res = m_snap->snap(pos);
    if (res.gp) {
        target = res.pos;
    }

    m_preview->setLine(QLineF(QPointF(m_first->model()->x(), m_first->model()->y()), target));
    m_scene->update();
}

void LineTool::mouseRelease(const QPointF&) {}