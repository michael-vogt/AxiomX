#include "circletool.h"

CircleTool::CircleTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm) : m_ctrl(c), m_interaction(im), m_scene(s), m_command(cm) {}

void CircleTool::resetTool() {
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

void CircleTool::mousePress(const QPointF& pos) {
    GraphicsPoint* p = m_interaction->getSnappedPoint(pos);
    if (!p) {
        auto cmd = new CreatePointCommand(m_ctrl, pos.x(), pos.y());
        m_command->execute(cmd);
        p = cmd->getResultGraphicsObject();
    }

    if (!m_first) {
        m_first = p;

        m_preview = new QGraphicsEllipseItem(0, 0, 0, 0);
        m_scene->addItem(m_preview);
        m_currentlyWorking = true;

    } else {
        auto cmd = new CreateCircleCommand(m_ctrl, m_first, p);
        m_command->execute(cmd);
        GraphicsCircle* circle = cmd->getResultGraphicsObject();

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

void CircleTool::mouseMove(const QPointF& pos) {
    if (!m_first) return;

    QPointF target = pos;
    GraphicsPoint* snap = m_interaction->getSnappedPoint(pos);
    if (snap) {
        target = QPointF(snap->model()->x(), snap->model()->y());
    }

    if (m_preview) {
        QPointF center(m_first->model()->x(), m_first->model()->y());
        double radius = QLineF(center, pos).length();
        m_preview->setRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius );
        m_scene->update();
    }
}