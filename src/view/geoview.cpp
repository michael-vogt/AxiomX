#include <QScrollBar>
#include "geoview.h"
#include "../core/utility.h"

GeoView::GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c) : QGraphicsView(s), m_commandManager(cmd), m_ctrl(c) {
    setMouseTracking(true);
    viewport()->setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    m_snap = new SnapManager(m_ctrl);
}

SnapManager* GeoView::snapManager() {
    return m_snap;
}

void GeoView::setSnapManager(SnapManager* sm) {
    m_snap = sm;
}

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
        m_ctrlPressed = true;
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
        m_showGrid = !m_showGrid;
        viewport()->update();
    }

}

void GeoView::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Control) {
        m_ctrlPressed = false;
    }
}

void GeoView::mouseMoveEvent(QMouseEvent* event) {
    if (m_panning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        viewport()->update();
        return;
    }

    QPointF pos = mapToScene(event->pos());
    if (m_snap) {
        auto result = m_snap->snap(pos);
        pos = result.pos;
        m_hasSnap = result.snapped;
        m_lastSnap = result.pos;
    } else {
        m_hasSnap = false;
    }

    bool toolCurrentlyWorking = (m_tool && m_tool->currentlyWorking());

    if (m_interaction && !toolCurrentlyWorking) {
        //QPointF snapped = m_snap ? m_snap->snap(pos) : pos;
        m_interaction->updateHover(pos);
    }

    if (m_tool) {
        m_tool->mouseMove(pos);
    }

    QGraphicsView::mouseMoveEvent(event);
    viewport()->update();
}

void GeoView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton || (event->button() == Qt::LeftButton && m_ctrlPressed)) {
        m_panning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        return;
    }

    QPointF pos = mapToScene(event->pos());
    /*if (m_snap)
        pos = m_snap->snap(pos);*/

    if (m_tool) {
        m_tool->mousePress(pos);
    }

    QGraphicsView::mousePressEvent(event);
}

void GeoView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton || (event->button() == Qt::LeftButton && m_ctrlPressed)) {
        m_panning = false;
        setCursor(Qt::ArrowCursor);
        viewport()->update();
        return;
    }

    QPointF pos = mapToScene(event->pos());
    /*if (m_snap)
        pos = m_snap->snap(pos);*/

    if (m_tool) {
        m_tool->mouseRelease(pos);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GeoView::wheelEvent(QWheelEvent* event) {
    const double scaleFactor = 1.15;
    QPointF scenePos = mapToScene(event->position().toPoint());
    if (event->angleDelta().y() > 0)
        scale(scaleFactor, scaleFactor);
    else
        scale(1/scaleFactor, 1/scaleFactor);

    QPointF newScenePos = mapToScene(event->position().toPoint());
    QPointF delta = newScenePos - scenePos;

    translate(delta.x(), delta.y());
}

void GeoView::drawBackground(QPainter *painter, const QRectF &rect) {
    if (!m_showGrid) {
        return;
    }

    double left = std::floor(rect.left() / m_gridSize) * m_gridSize;
    double top = std::floor(rect.top() / m_gridSize) * m_gridSize;

    double x = left;
    while (x < rect.right()) {
        if (fmod(x, m_gridSize * 5) == 0)
            painter->setPen(QPen(Qt::gray, 0));
        else
            painter->setPen(QPen(QColor(220, 220, 220), 0));
        painter->drawLine(QLineF(x, rect.top(), x, rect.bottom()));
        x += m_gridSize;
    }

    double y = top;
    while (y < rect.bottom()) {
        if (fmod(y, m_gridSize * 5) == 0)
            painter->setPen(QPen(Qt::gray, 0));
        else
            painter->setPen(QPen(QColor(220, 220, 220), 0));
        painter->drawLine(QLineF(rect.left(), y, rect.right(), y));
        y += m_gridSize;
    }

    if (m_showAxes) {
        drawAxes(painter, rect);
    }
}

void GeoView::drawForeground(QPainter *painter, const QRectF &rect) {
    if (!m_hasSnap) return;

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);

    painter->drawEllipse(m_lastSnap, 4, 4);
};

void GeoView::drawAxes(QPainter* painter, const QRectF& rect) {
    QPen axisPen(Qt::black, 0);
    painter->setPen(axisPen);

    // Y-Achse (x = 0)
    if (rect.left() <= 0 && rect.right() >= 0) {
        painter->drawLine(QLineF(0, rect.top(), 0, rect.bottom()));
    }

    // X-Achse (y = 0)
    if (rect.top() <= 0 && rect.bottom() >= 0) {
        painter->drawLine(QLineF(rect.left(), 0, rect.right(), 0));
    }
}

