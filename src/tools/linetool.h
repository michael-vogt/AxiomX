#ifndef LINETOOL_H
#define LINETOOL_H

#include <iostream>
#include "../control/interactionmanager.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../command/createlinecommand.h"
#include "../tools/tool.h"

class LineTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;
    CommandManager* m_command;

    GraphicsPoint* m_first = nullptr;
    QGraphicsLineItem* m_preview = nullptr;

public:
    LineTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm) : m_ctrl(c), m_interaction(im), m_scene(s), m_command(cm) {}

    void resetTool() override {
        if (m_preview) {
            m_scene->removeItem(m_preview);
            delete m_preview;
            m_preview = nullptr;
        }

        if (m_first) {
            m_scene->removeItem(m_first);
            m_first = nullptr;
        }
    }

    void mousePress(const QPointF &pos) override {
        GraphicsPoint* p = m_interaction->getSnappedPoint(pos);
        if (!p) {
            auto cmd = new CreatePointCommand(m_ctrl, pos.x(), pos.y());
            m_command->execute(cmd);
            p = cmd->getResultGraphicsObject();
        }

        if (!m_first) {
            m_first = p;

            QPen pen(Qt::DashLine);
            pen.setColor(Qt::gray);
            pen.setWidth(2);
            m_preview = m_scene->addLine(QLineF(pos, pos), pen);
        } else {
            m_command->execute(new CreateLineCommand(m_ctrl, m_first, p));

            if (m_preview) {
                m_scene->removeItem(m_preview);
                delete m_preview;
                m_preview = nullptr;
            }

            m_first = nullptr;
        }
    }

    void mouseMove(const QPointF& pos) override {
        if (!m_first || !m_preview) return;

        QPointF target = pos;
        GraphicsPoint* snap = m_interaction->getSnappedPoint(pos);
        if (snap) {
            target = QPointF(snap->model()->x(), snap->model()->y());
        }

        m_preview->setLine(QLineF(QPointF(m_first->model()->x(), m_first->model()->y()), target));
    }

    void mouseRelease(const QPointF&) override {}
};

#endif // LINETOOL_H
