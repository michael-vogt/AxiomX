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

public:
    GeoView(QGraphicsScene* s) : QGraphicsView(s) {
        setMouseTracking(true);
        viewport()->setMouseTracking(true);
    }

    void setTool(Tool* t) {
        m_tool = t;
    }

    void setInteractionManager(InteractionManager* im) {
        m_interaction = im;
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        if (event->key() == Qt::Key_Escape && m_tool) {
            m_tool->resetTool();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        QPointF pos = mapToScene(event->pos());

        if (m_interaction) {
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
