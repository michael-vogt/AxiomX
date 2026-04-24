#include <QApplication>
#include "selecttool.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"
#include "../view/graphicspoint.h"

SelectTool::SelectTool(SceneController* c, SelectionManager* s, QGraphicsScene* sc) : Tool(nullptr), m_ctrl(c), m_selection(s), m_scene(sc) {
    m_dragRectPen.setColor(Qt::darkGray);
}

void SelectTool::mousePress(const QPointF& pos) {
    m_dragging = true;
    m_dragStart = pos;

    m_rect = m_scene->addRect(QRectF(pos, pos), m_dragRectPen, m_dragRectBrush);
    m_rect->setZValue(1000);
}

void SelectTool::mouseMove(const QPointF &pos) {
    if (!m_dragging || !m_rect) return;

    QRectF r(m_dragStart, pos);
    m_rect->setRect(r.normalized());
}

void SelectTool::mouseRelease(const QPointF& pos) {
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

            // Kreise
            if (auto gc = dynamic_cast<GraphicsCircle*>(g)) {
                QRectF circleBox = gc->boundingRect();
                if (selectionRect.contains(circleBox)) {
                    if (!m_selection->isSelected(gc)) {
                        m_selection->select(gc, true);
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

void SelectTool::resetTool() {}