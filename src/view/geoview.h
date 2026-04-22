#ifndef GEOVIEW_H
#define GEOVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "../tools/tools.h"
#include "../control/interactionmanager.h"
#include "../core/utility.h"
#include "grid.h"

class GeoView : public QGraphicsView {
private:
    Tool* m_tool = nullptr;
    InteractionManager* m_interaction = nullptr;
    CommandManager* m_commandManager = nullptr;
    SceneController* m_ctrl = nullptr;
    Grid* m_grid = nullptr;
    double m_zoomFactor = 1.0;

public:
    GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c) : QGraphicsView(s), m_commandManager(cmd), m_ctrl(c) {
        setMouseTracking(true);
        viewport()->setMouseTracking(true);        
        m_grid = new Grid(sceneRect().center(), sceneRect());
    }

    Grid* grid() { return m_grid; }

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

        if (event->key() == Qt::Key_Delete) {
            m_ctrl->deleteSelected();
            scene()->update();
        }

        if (event->key() == Qt::Key_NumberSign) {
            for (QLineF line : m_grid->gridLines()) {
                qDebug() << line;
            }
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

    void wheelEvent(QWheelEvent* event) override {
        event->accept();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        if (event->angleDelta().y() > 0) {
            scale(1.25, 1.25);
        } else {
            scale(0.8, 0.8);
        }
    }

    void drawBackground(QPainter *painter, const QRectF &rect) override {
        if (!m_grid) return;

        setSceneRect(viewport()->contentsRect());
        m_grid->update(sceneRect());
        m_grid->paint(painter);

        /*for (QLineF line : m_grid->gridLines()) {
            qDebug() << line;
            painter->drawLine(line);
        }*/

        /*QLineF line(0, 0, 100, 0);
        painter->drawLine(line.translated(-50, 0));
        painter->drawLine(line.translated(0, 10));*/
        /*for (QLineF line : m_grid->gridLines()) {
            painter->drawLine(line.translated(sceneRect().center()));
        }*/
    }


};

#endif // GEOVIEW_H
