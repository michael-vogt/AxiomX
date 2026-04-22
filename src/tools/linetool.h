#ifndef LINETOOL_H
#define LINETOOL_H

#include <iostream>
#include "../control/interactionmanager.h"
#include "../command/commandmanager.h"
#include "../command/createpointcommand.h"
#include "../command/createlinecommand.h"
#include "../tools/tool.h"
#include "../core/utility.h"

class LineTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;
    CommandManager* m_command;

    GraphicsPoint* m_first = nullptr;
    //GraphicsPoint* m_temporary = nullptr;
    InfiniteLineItem* m_preview = nullptr;

    LineType m_lineType = LineType::LINE;

public:
    LineTool(SceneController* c, InteractionManager* im, QGraphicsScene* s, CommandManager* cm) : m_ctrl(c), m_interaction(im), m_scene(s), m_command(cm) {}

    LineType lineType() {
        return m_lineType;
    }

    void setLineType(LineType lineType) {
        m_lineType = lineType;
    }

    void toggleLineType() {
        if (m_lineType == LineType::SEGMENT) {
            m_lineType = LineType::RAY;
        } else if (m_lineType == LineType::RAY) {
            m_lineType = LineType::LINE;
        } else {
            m_lineType = LineType::SEGMENT;
        }
    }

    void resetTool() override {
        bool update = (m_preview || m_first/* || m_temporary*/);
        if (m_preview) {
            m_scene->removeItem(m_preview);
            delete m_preview;
            m_preview = nullptr;
        }

        if (m_first) {
            m_scene->removeItem(m_first);
            m_first = nullptr;
        }

        /*if (m_temporary) {
            m_ctrl->remove(m_temporary);
            delete m_temporary;
            m_temporary = nullptr;
        }*/

        m_currentlyWorking = false;

        if (update) {
            m_scene->update();
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
            /*auto cmd = new CreatePointCommand(m_ctrl, pos.x(), pos.y(), true);
            m_command->execute(cmd);
            m_temporary = cmd->getResultGraphicsObject();*/

            QPen pen(Qt::DashLine);
            pen.setColor(Qt::gray);
            pen.setWidth(2);

            m_preview = new InfiniteLineItem(m_lineType);
            m_preview->setLine(QLineF(pos, pos));
            m_preview->setPen(pen);
            m_scene->addItem(m_preview);

            m_currentlyWorking = true;
        } else {
            auto cmd = new CreateLineCommand(m_ctrl, m_first, p, m_lineType);
            m_command->execute(cmd);
            GraphicsLine* line = cmd->getResultGraphicsObject();

            /*if (m_temporary) {
                GraphicsPoint* tmp = m_ctrl->graphicsPointAlreadyExists(m_temporary);
                if (tmp) {
                    m_ctrl->remove(m_temporary);
                    tmp->model()->addDependent(line->model());
                } else {
                    m_temporary->model()->addDependent(line->model());
                }
            }*/

            if (m_preview) {
                m_scene->removeItem(m_preview);
                delete m_preview;
                m_preview = nullptr;
            }

            m_first = nullptr;
            m_scene->update();
            m_currentlyWorking = false;

            //printGraphicsObjectsToConsole(m_ctrl->graphics());
        }
    }

    void mouseMove(const QPointF& pos) override {
        if (!m_first || !m_preview) return;

        QPointF target = pos;
        GraphicsPoint* snap = m_interaction->getSnappedPoint(pos);
        if (snap) {
            target = QPointF(snap->model()->x(), snap->model()->y());
        }

        /*if (m_temporary) {
            m_temporary->model()->set(target.x(), target.y());
        }*/

        m_preview->setLine(QLineF(QPointF(m_first->model()->x(), m_first->model()->y()), target));
        m_scene->update();
    }

    void mouseRelease(const QPointF&) override {}
};

#endif // LINETOOL_H
