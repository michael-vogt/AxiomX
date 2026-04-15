#ifndef LINETOOL_H
#define LINETOOL_H

#include <iostream>
//#include "../control/interactionmanager.h"

class LineTool : public Tool {
private:
    SceneController* m_ctrl;
    InteractionManager* m_interaction;
    QGraphicsScene* m_scene;

    Point* m_first = nullptr;
    QGraphicsLineItem* m_preview = nullptr;

public:
    LineTool(SceneController* c, InteractionManager* im, QGraphicsScene* s) : m_ctrl(c), m_interaction(im), m_scene(s) {}

    void resetTool() override {
        if (m_preview) {
            m_scene->removeItem(m_preview);
            delete m_preview;
            m_preview = nullptr;
        }

        m_first = nullptr;
    }

    void mousePress(const QPointF &pos) override {
        Point* p = m_interaction->getSnappedPoint(pos); // ctrl->findPointNear(pos);
        if (!p) {
            p = m_ctrl->createPoint(pos.x(), pos.y());
        }

        if (!m_first) {
            m_first = p;

            QPen pen(Qt::DashLine);
            pen.setColor(Qt::gray);
            pen.setWidth(2);
            m_preview = m_scene->addLine(QLineF(pos, pos), pen);
        } else {
            m_ctrl->createLine(m_first, p);

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
        Point* snap = m_interaction->getSnappedPoint(pos); // ctrl->findPointNear(pos);
        if (snap) {
            target = QPointF(snap->x(), snap->y());
        }

        m_preview->setLine(QLineF(QPointF(m_first->x(), m_first->y()), target));
    }

    void mouseRelease(const QPointF&) override {}
};

#endif // LINETOOL_H
