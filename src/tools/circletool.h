#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "tool.h"
#include "../control/interactionmanager.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../command/createcirclecommand.h"

class CircleTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;
    CommandManager* m_command;

    GraphicsPoint* m_first = nullptr;
    QGraphicsEllipseItem* m_preview = nullptr;

public:
    CircleTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm) : m_ctrl(c), m_interaction(im), m_scene(s), m_command(cm) {}

    void resetTool() override {
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

    void mousePress(const QPointF& pos) override {
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

    void mouseMove(const QPointF& pos) override {
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

};

#endif // CIRCLETOOL_H
