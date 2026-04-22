#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include <QApplication>
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
    SelectTool(SceneController* c, SelectionManager* s, QGraphicsScene* sc);

    void mousePress(const QPointF& pos) override;

    void mouseMove(const QPointF &pos) override;

    void mouseRelease(const QPointF& pos) override;

    void resetTool() override;
};

#endif // SELECTTOOL_H
