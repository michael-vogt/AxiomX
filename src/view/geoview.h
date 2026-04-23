#ifndef GEOVIEW_H
#define GEOVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "../command/commandmanager.h"
#include "../control/interactionmanager.h"
#include "../tools/tool.h"

class GeoView : public QGraphicsView {
private:
    Tool* m_tool = nullptr;
    InteractionManager* m_interaction = nullptr;
    CommandManager* m_commandManager = nullptr;
    SceneController* m_ctrl = nullptr;
    double m_gridSize = 50.0;
    bool m_showGrid = true;
    bool m_showAxes = true;
    bool m_panning = false;
    QPoint m_lastMousePos;

public:

    GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c);

    Tool* tool();

    void setTool(Tool* t);

    void setInteractionManager(InteractionManager* im);

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void drawAxes(QPainter* painter, const QRectF& rect);

};

#endif // GEOVIEW_H
