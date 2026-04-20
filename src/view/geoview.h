#ifndef GEOVIEW_H
#define GEOVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "../tools/tools.h"
#include "../control/interactionmanager.h"

class GeoView : public QGraphicsView {
private:
    Tool* m_tool = nullptr;
    InteractionManager* m_interaction = nullptr;
    CommandManager* m_commandManager = nullptr;
    SceneController* m_ctrl = nullptr;

public:
    GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c) : QGraphicsView(s), m_commandManager(cmd), m_ctrl(c) {
        setMouseTracking(true);
        viewport()->setMouseTracking(true);
    }

    Tool* tool() {
        return m_tool;
    }

    void setTool(Tool* t) {
        m_tool = t;
    }

    void setInteractionManager(InteractionManager* im) {
        m_interaction = im;
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        if (event->modifiers() & Qt::ControlModifier) {
            if (event->key() == Qt::Key_Z) {
                m_commandManager->undo();
                this->scene()->update();
            } else if (event->key() == Qt::Key_Y) {
                m_commandManager->redo();
                this->scene()->update();
            } else if (event->key() == Qt::Key_V) {
                printGraphicsObjectsToConsole(m_ctrl->graphics());
            }
        }

        if (event->key() == Qt::Key_Escape && m_tool) {
            m_tool->resetTool();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        QPointF pos = mapToScene(event->pos());

        bool toolCurrentlyWorking = (m_tool && m_tool->currentlyWorking());

        if (m_interaction && !toolCurrentlyWorking) {
            m_interaction->updateHover(pos);
        }

        if (m_tool) {
            m_tool->mouseMove(pos);
        }

        QGraphicsView::mouseMoveEvent(event);
    }

    void mousePressEvent(QMouseEvent* event) override {
        QPointF pos = mapToScene(event->pos());

        if (m_tool) {
            m_tool->mousePress(pos);
        }

        QGraphicsView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        QPointF pos = mapToScene(event->pos());

        if (m_tool) {
            m_tool->mouseRelease(pos);
        }

        QGraphicsView::mouseReleaseEvent(event);
    }
};

#endif // GEOVIEW_H
