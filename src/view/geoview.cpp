#include "geoview.h"
#include "../core/utility.h"

GeoView::GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c) : QGraphicsView(s), m_commandManager(cmd), m_ctrl(c) {
    setMouseTracking(true);
    viewport()->setMouseTracking(true);
    m_grid = new Grid(sceneRect().center(), sceneRect());
}

Grid* GeoView::grid() { return m_grid; }

Tool* GeoView::tool() {
    return m_tool;
}

void GeoView::setTool(Tool* t) {
    m_tool = t;
}

void GeoView::setInteractionManager(InteractionManager* im) {
    m_interaction = im;
}

void GeoView::keyPressEvent(QKeyEvent* event) {
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

void GeoView::mouseMoveEvent(QMouseEvent* event) {
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

void GeoView::mousePressEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());

    if (m_tool) {
        m_tool->mousePress(pos);
    }

    QGraphicsView::mousePressEvent(event);
}

void GeoView::mouseReleaseEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());

    if (m_tool) {
        m_tool->mouseRelease(pos);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GeoView::wheelEvent(QWheelEvent* event) {
    event->accept();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->angleDelta().y() > 0) {
        scale(1.25, 1.25);
    } else {
        scale(0.8, 0.8);
    }
}

void GeoView::drawBackground(QPainter *painter, const QRectF &rect) {
    if (!m_grid) return;

    setSceneRect(viewport()->contentsRect());
    m_grid->update(sceneRect());
    m_grid->paint(painter);
}