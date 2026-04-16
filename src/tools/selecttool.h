#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tool.h"
#include "../control/scenecontroller.h"
#include "../control/selectionmanager.h"

class SelectTool : public Tool {
private:
    SceneController* m_ctrl;
    SelectionManager* m_selection;
    QGraphicsScene* m_scene;

    QPointF m_dragStart;
    QGraphicsRectItem* m_rect = nullptr;
    bool m_dragging = false;

    QPen m_dragRectPen = QPen(Qt::DashLine);
    QBrush m_dragRectBrush = QBrush(QColor(100, 100, 255, 50));

public:
    SelectTool(SceneController* c, SelectionManager* s, QGraphicsScene* sc) : m_ctrl(c), m_selection(s), m_scene(sc) {
        m_dragRectPen.setColor(Qt::darkGray);
    }

    void mousePress(const QPointF& pos) override {
        m_dragging = true;
        m_dragStart = pos;

        m_rect = m_scene->addRect(QRectF(pos, pos), m_dragRectPen, m_dragRectBrush);
        m_rect->setZValue(1000);
    }

    void mouseMove(const QPointF &pos) override {
        if (!m_dragging || !m_rect) return;

        QRectF r(m_dragStart, pos);
        m_rect->setRect(r.normalized());
    }

    void mouseRelease(const QPointF& pos) override {
        if (QLineF(m_dragStart, pos).length() < 3.0) {
            bool multi = QApplication::keyboardModifiers() & Qt::ShiftModifier;
            auto obj = m_ctrl->findObjectAt(pos);
            if (!obj) {
                m_selection->clear();
            } else {
                m_selection->select(obj, multi);
            }

            m_dragging = false;
            if (m_rect) {
                m_scene->removeItem(m_rect);
                delete m_rect;
                m_rect = nullptr;
            }

        } else {

            if (!m_dragging) return;
            m_dragging = false;
            QRectF selectionRect(m_dragStart, pos);
            selectionRect = selectionRect.normalized();

            bool multi = QApplication::keyboardModifiers() & Qt::ShiftModifier;
            if (!multi) {
                m_selection->clear();
            }

            for (auto g : m_ctrl->graphics()) {
                // Punkte
                if (auto gp = dynamic_cast<GraphicsPoint*>(g)) {
                    if (selectionRect.contains(gp->pos())) {
                        if (!m_selection->isSelected(gp)) {
                            m_selection->select(gp, true);
                        }
                    }
                }

                // Linien
                if (auto gl = dynamic_cast<GraphicsLine*>(g)) {
                    QRectF lineBox = gl->boundingRect().translated(gl->pos());
                    if (selectionRect.contains(lineBox)) {
                        if (!m_selection->isSelected(gl)) {
                            m_selection->select(gl, true);
                        }
                    }
                }
            }

            m_scene->removeItem(m_rect);
            delete m_rect;
            m_rect = nullptr;
        }

        m_scene->update();

    }

    void resetTool() override {}
};

#endif // SELECTTOOL_H
